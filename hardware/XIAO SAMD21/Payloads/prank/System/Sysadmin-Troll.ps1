$PShellProfile = "$env:USERPROFILE\Documents\WindowsPowershell\Microsoft.Powershell_profile.ps1"

cd $env:USERPROFILE\Documents
New-Item WindowsPowershell -ItemType Directory -ErrorAction SilentlyContinue | Out-Null
cd WindowsPowershell
New-Item Microsoft.Powershell_profile.ps1 -ItemType File -ErrorAction SilentlyContinue | Out-Null

Add-Content -Path $PShellProfile -Value "function Troll"
Add-Content -Path $PShellProfile -Value "{"
Add-Content -Path $PShellProfile -Value "`t`$i = 1"
Add-Content -Path $PShellProfile -Value "`tdo {`$i; `$i++"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 300"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 300"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(932,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 150"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(1047,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 150"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 300"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 300"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(699,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 150"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(740,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 150"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 300"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 300"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(932,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 150"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(1047,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 150"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 300"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 300"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(699,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 150"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(740,150)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 150"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(932,150)"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(587,1200)"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(587,1200)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 75"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(932,150)"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(554,1200)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 75"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(932,150)"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(784,150)"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(523,1200)"
Add-Content -Path $PShellProfile -Value "`tStart-Sleep -m 150"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(466,150)"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(466,150)"
Add-Content -Path $PShellProfile -Value "`t[console]::beep(523,150)"
Add-Content -Path $PShellProfile -Value  "`t} until (`$i -gt 500)"
Add-Content -Path $PShellProfile -Value "}"

Add-Content -Path $PShellProfile -Value "`n`nSet-Alias -Name ipconfig -Value Troll"
Add-Content -Path $PShellProfile -Value "Set-Alias -Name nslookup -Value Troll"
Add-Content -Path $PShellProfile -Value "Set-Alias -Name ping -Value Troll"