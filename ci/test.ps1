Write-Host 'Running test script...'

# go to the test binary dir
Set-Location ./build/tests    

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

# go back to the project's dir
Set-Location ../
