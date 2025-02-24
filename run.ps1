$source = ".\src"  

Write-Host "Compiling C++ files from $source..."
g++ $source\main.cpp $source\Logic.cpp $source\Var.cpp

if ($?) {
    Write-Host "Compilation successful."
} else {
    Write-Host "Compilation failed."
    exit 1  
}

Write-Host "Running..."
Write-Host ""
.\a.exe
