Write-Host 'Running test script...'

$curBuildCombo = $env:BUILD_COMBO

$isMingwBuild = $curBuildCombo -eq 'windows-mingw'
$isMsvcBuild = $curBuildCombo -eq 'windows-msvc'

# go to the test binary dir
Push-Location ./build/tests

if ($isLinux) {
    ./pkg_test
}
elseif ($isWindows) {   
    if ($isMingwBuild) {        
        # copy libuncso2 and crypto++ dlls to the tests directory
        Copy-Item "..\libuncso2.dll" -Destination ".\"
        Copy-Item "..\external\cryptopp\libcryptopp.dll" -Destination ".\"
    }
    elseif ($isMsvcBuild) {        
        # copy libuncso2 dll to the tests directory
        Copy-Item "..\uncso2.dll" -Destination ".\"
    }

    ./pkg_test.exe
}
else {
    Write-Error 'An unknown OS is running this script, implement me.'
    exit 1
}

if ($LASTEXITCODE -ne 0) {
    Write-Error 'One or more tests failed.'
    exit 1
}

# go back to the project's dir
Pop-Location
