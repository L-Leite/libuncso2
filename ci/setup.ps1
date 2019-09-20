function CreateDirectory {
    param( [string]$newDirectory)
    New-Item -ItemType Directory -Path $newDirectory
}

function SetupVsToolsPath {
    # from https://allen-mack.blogspot.com/2008/03/replace-visual-studio-command-prompt.html
    Push-Location 'C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build'

    cmd /c "vcvars64.bat&set" |
    ForEach-Object {
        if ($_ -match "=") {
            $v = $_.split("="); set-item -force -path "ENV:\$($v[0])"  -value "$($v[1])"
        }
    }

    Pop-Location
}

function PrintToolsVersion {
    param ([string]$curBuildCombo)

    Write-Host '#'
    Write-Host '# TOOLS VERSIONS'
    Write-Host '#'

    switch ($curBuildCombo) {
        "linux-gcc" {
            which gcc-9
            Write-Host '# GCC'
            gcc-9 -v
        }
        "linux-clang" {
            which clang-8
            Write-Host '# Clang - GCC/Linux'
            clang-8 -v
        }
        "windows-mingw" {
            Write-Host '# MinGW'
            C:\msys64\mingw64\bin\gcc.exe -v
        }
        "windows-msvc" {
            which cl
            Write-Host '# MSVC'
            cl
        }
        "windows-clang" {
            which clang-cl
            Write-Host '# Clang - Windows'
            clang-cl -v
        }
        Default {
            Write-Error 'Unknown build combo used, could not find appropriate compiler.'
            exit 1
        }
    }
    
    Write-Host '# CMake'
    cmake --version

    Write-Host '# Ninja'
    ninja --version

    Write-Host '# Git'
    git --version

    Write-Host '#'
    Write-Host '# END OF TOOLS VERSIONS'
    Write-Host '#'
}

$curBuildCombo = $env:BUILD_COMBO

#$isGccBuild = $curBuildCombo -eq 'linux-gcc' # unused
$isLinuxClangBuild = $curBuildCombo -eq 'linux-clang'
# $isMingwBuild = $curBuildCombo -eq 'windows-mingw' # unused
$isMsvcBuild = $curBuildCombo -eq 'windows-msvc'
$isWinClangBuild = $curBuildCombo -eq 'windows-clang'

Write-Host 'Running setup script...'
Write-Host 'Current setup build combo is: $curBuildCombo'

if ($isLinux) {
    # install ninja through apt
    sudo apt install ninja-build

    if ($isLinuxClangBuild) {
        # retrieve clang 8
        sudo add-apt-repository "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-8 main"
        sudo apt update
        sudo apt install clang-8 lldb-8 lld-8 libc++-8-dev libc++abi-8-dev
    }
}
elseif ($isWindows) {
    # install scoop
    Invoke-WebRequest -useb get.scoop.sh | Invoke-Expression

    # install ninja through scoop
    scoop install ninja

    if ($isMsvcBuild -or $isWinClangBuild) {
        # add msvc 17 tools to path
        SetupVsToolsPath
    }
}
else {
    Write-Error 'An unknown OS is running this script, implement me.'
    exit 1
}

# print tools versions
PrintToolsVersion $curBuildCombo

# setup submodules
git submodule update --init --recursive

# create build dir
CreateDirectory ./build
