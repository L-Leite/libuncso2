Write-Host 'Running test script...'

# go to the test binary dir
Push-Location ./build/tests    

if ($isLinux) {
    ./pkg_test
}
elseif ($isWindows) {    
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
