$curBuildCombo = $env:BUILD_COMBO

Write-Host 'Running build script...'
Write-Host 'Current script build combo is: $curBuildCombo'

$targetCompilerCC;
$targetCompilerCXX;

switch ($curBuildCombo) {
    "linux-gcc" {
        $targetCompilerCC = 'gcc-9'
        $targetCompilerCXX = 'g++-9'
    }
    "linux-clang" {
        $targetCompilerCC = 'clang-8'
        $targetCompilerCXX = 'clang++-8'
    }
    "windows-mingw" {
        $targetCompilerCC = 'C:\\msys64\\mingw64\\bin\\gcc.exe'
        $targetCompilerCXX = 'C:\\msys64\\mingw64\\bin\\g++.exe'
    }
    "windows-msvc" {
        $targetCompilerCC = 'cl'
        $targetCompilerCXX = 'cl'
    }
    "windows-clang" {
        $targetCompilerCC = 'clang-cl'
        $targetCompilerCXX = 'clang-cl'
    }
    Default {
        Write-Error 'Unknown build combo used, could not find appropriate compiler.'
        exit 1
    }
}

Write-Host 'Selected C compiler: $targetCompilerCC'
Write-Host 'Selected C++ compiler: $targetCompilerCXX'

# go to build dir
Push-Location ./build

cmake -G "Ninja" `
    -DCMAKE_CXX_COMPILER="$targetCompilerCXX" `
    -DCMAKE_C_COMPILER="$targetCompilerCC" `
    ../

if ($LASTEXITCODE -ne 0) {
    Write-Error '#'
    Write-Error '# BUILD ERROR'
    Write-Error '# Failed to generate CMake configuration files.'
    Write-Error '#'
    exit 1
}

ninja all

if ($LASTEXITCODE -ne 0) {
    Write-Error '#'
    Write-Error '# BUILD ERROR'
    Write-Error '# Failed to build project.'
    Write-Error '#'
    exit 1
}

# go back to the project's dir
Pop-Location
