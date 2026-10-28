$ErrorActionPreference = 'Stop'
$taskWorkspace = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '../../../..'))
$taskCompilerBin = Join-Path $taskWorkspace 'work/devdocqa-build/msys/ucrt64/bin'
$taskCompiler = Join-Path $taskCompilerBin 'clang++.exe'
if (-not (Test-Path -LiteralPath $taskCompiler)) { throw 'Prepared C++ compiler not found.' }
$taskBuild = Join-Path $taskWorkspace 'work/interview-pack-check/2026-10-28-weak'
New-Item -ItemType Directory -Path $taskBuild -Force | Out-Null
$taskCpp = Join-Path $taskBuild 'exercise.cpp'
$taskExe = Join-Path $taskBuild 'exercise.exe'
Copy-Item -LiteralPath (Join-Path $PSScriptRoot '03_weak_ptr动手练习.cpp') -Destination $taskCpp -Force
$taskOldPath = $env:PATH
try {
    $env:PATH = $taskCompilerBin + ';' + $env:PATH
    & $taskCompiler -std=c++17 -Wall -Wextra -pedantic $taskCpp -o $taskExe
    if ($LASTEXITCODE -ne 0) { throw 'Compilation failed.' }
    & $taskExe
    if ($LASTEXITCODE -ne 0) { throw 'Exercise is incomplete or tests failed. Read the output above.' }
} finally {
    $env:PATH = $taskOldPath
}
