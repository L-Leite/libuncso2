function CreateDirectory {
    param( [string]$newDirectory)
    New-Item -ItemType Directory -Path $newDirectory
}

$curBuildCombo = $env:BUILD_COMBO

Write-Host 'Running setup script...'
Write-Debug 'Current setup build combo is: $curBuildCombo'

if ($isLinux) {
    $isGccBuild = $curBuildCombo -eq 'linux-gcc'
    $isLinuxClangBuild = $curBuildCombo -eq 'linux-gcc'

    # install ninja through apt
    sudo apt install ninja

    if ($isGccBuild) {        
        # retrieve latest gcc
        sudo add-apt-repository ppa:ubuntu-toolchain-r/test
        sudo apt update
        sudo apt install gcc-9

        gcc-9 -v
    }
    elseif ($isLinuxClangBuild) {
        # retrieve clang 8
        sudo add-apt-repository "deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-8 main"
        sudo apt update
        sudo apt install clang-8 lldb-8 lld-8 libc++-8-dev libc++abi-8-dev

        clang-8 -v
    }
}
elseif ($isWindows) {
    $isMingwBuild = $curBuildCombo -eq 'windows-mingw'
    $isMsvcBuild = $curBuildCombo -eq 'windows-msvc'
    $isWinClangBuild = $curBuildCombo -eq 'windows-clang'

    # install scoop
    Invoke-WebRequest -useb get.scoop.sh | Invoke-Expression

    # install ninja through scoop
    scoop install ninja

    if ($isMsvcBuild -or $isWinClangBuild) {
        # add msvc 17 tools to path
        "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat x86_amd64"
    }

    if ($isMsvcBuild) {
        cl
    }
    elseif ($isWinClangBuild) {
        clang-cl -v
    }
    elseif ($isMingwBuild) {
        gcc -v
    }
}
else {
    Write-Error 'An unknown OS is running this script, implement me.'
    exit 1
}

# print tools versions
cmake -v
ninja -v

# setup submodules
git submodule update --init --recursive

# create build dir
CreateDirectory build
Set-Location ./build