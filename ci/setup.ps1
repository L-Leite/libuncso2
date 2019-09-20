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

    Write-Debug ''
    Write-Debug '#'
    Write-Debug '# TOOLS VERSIONS'
    Write-Debug '#'
    Write-Debug ''

    switch ($curBuildCombo) {
        "linux-gcc" {
            Write-Debug '# GCC'
            gcc-9 -v
        }
        "linux-clang" {
            Write-Debug '# Clang - GCC/Linux'
            clang -v
        }
        "windows-mingw" {
            Write-Debug '# MinGW'
            C:\msys64\mingw64\bin\gcc.exe -v
        }
        "windows-msvc" {
            Write-Debug '# MSVC'
            cl
        }
        "windows-clang" {
            Write-Debug '# Clang - Windows'
            clang-cl -v
        }
        Default {
            Write-Error 'Unknown build combo used, could not find appropriate compiler.'
            exit 1
        }
    }
    
    Write-Debug '# CMake'
    cmake --version
    Write-Debug ''

    Write-Debug '# Ninja'
    ninja --version
    Write-Debug ''

    Write-Debug '# Git'
    git --version
    Write-Debug ''

    Write-Debug ''
    Write-Debug '#'
    Write-Debug '# END OF TOOLS VERSIONS'
    Write-Debug '#'
    Write-Debug ''
}

$curBuildCombo = $env:BUILD_COMBO

$isGccBuild = $curBuildCombo -eq 'linux-gcc'
$isLinuxClangBuild = $curBuildCombo -eq 'linux-clang'
# $isMingwBuild = $curBuildCombo -eq 'windows-mingw' # unused
$isMsvcBuild = $curBuildCombo -eq 'windows-msvc'
$isWinClangBuild = $curBuildCombo -eq 'windows-clang'

Write-Host 'Running setup script...'
Write-Debug 'Current setup build combo is: $curBuildCombo'

if ($isLinux) {
    # install ninja through apt
    apt install ninja

    if ($isGccBuild) {        
        # retrieve latest gcc
        add-apt-repository ppa:ubuntu-toolchain-r/test
        apt update
        apt install gcc-9
    }
    elseif ($isLinuxClangBuild) {
        # retrieve clang 8
        add-apt-repository "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-8 main"
        apt update
        apt install clang-8 lldb-8 lld-8 libc++-8-dev libc++abi-8-dev
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
