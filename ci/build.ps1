function SetupVsToolsPath {
    # from https://allen-mack.blogspot.com/2008/03/replace-visual-studio-command-prompt.html

    # split location to shorten the command
    Push-Location 'C:\Program Files (x86)\Microsoft Visual Studio\2017'
    Push-Location '.\Community\VC\Auxiliary\Build'

    cmd /c "vcvars64.bat&set" |
    ForEach-Object {
        if ($_ -match "=") {
            $v = $_.split("="); set-item -force -path "ENV:\$($v[0])"  -value "$($v[1])"
        }
    }

    Pop-Location
    Pop-Location
}

$curBuildCombo = $env:BUILD_COMBO
$curConfig = $env:CONFIGURATION

Write-Host "Running build script..."
Write-Host "Current script build combo is: $curBuildCombo $curConfig"

$targetCompilerCC = '';
$targetCompilerCXX = '';

switch ($curBuildCombo) {
    "linux-gcc" {
        $targetCompilerCC = 'gcc-9'
        $targetCompilerCXX = 'g++-9'
        break
    }
    "linux-clang" {
        $targetCompilerCC = 'clang-8'
        $targetCompilerCXX = 'clang++-8'
        break
    }
    "windows-mingw" {
        $targetCompilerCC = 'C:\\msys64\\mingw64\\bin\\gcc.exe'
        $targetCompilerCXX = 'C:\\msys64\\mingw64\\bin\\g++.exe'
        break
    }
    "windows-msvc" {
        $targetCompilerCC = 'cl'
        $targetCompilerCXX = 'cl'
        # add msvc 17 tools to path
        SetupVsToolsPath
        break
    }
    "windows-clang" {
        $targetCompilerCC = 'clang'
        $targetCompilerCXX = 'clang'
        # add msvc 17 tools to path
        #SetupVsToolsPath
        break
    }
    Default {
        Write-Error 'Unknown build combo used, could not find appropriate compiler.'
        exit 1
    }
}

Write-Host "Selected C compiler: $targetCompilerCC"
Write-Host "Selected C++ compiler: $targetCompilerCXX"

# create build dir
CreateDirectory ./build

# go to build dir
Push-Location ./build

cmake -G "Ninja" `
    -DCMAKE_CXX_COMPILER="$targetCompilerCXX" `
    -DCMAKE_C_COMPILER="$targetCompilerCC" `
    -DCMAKE_BUILD_TYPE="$curConfig" `
    ../

if ($LASTEXITCODE -ne 0) {
    Write-Error 'Failed to generate CMake configuration files.'
    exit 1
}

ninja all

if ($LASTEXITCODE -ne 0) {
    Write-Error 'Failed to build project.'
    exit 1
}

# go back to the project's dir
Pop-Location
