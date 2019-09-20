Write-Host 'Running test script...'

Set-Location ./tests    

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
