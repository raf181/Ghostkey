# Define variables for the cargo delivery endpoint and file path
$endpoint = "http://192.168.10.62:5000/cargo_delivery"  # Replace with your actual server endpoint
$fileToUpload = "Preparer.ps1"  # Replace with the path to your file

# Define parameters required for cargo delivery
$espID = "your_esp_id"
$deliveryKey = "your_delivery_key"
$encryptionPassword = "your_encryption_password"

# Create hashtable for form data
$formData = @{
    esp_id = $espID
    delivery_key = $deliveryKey
    encryption_password = $encryptionPassword
    file = Get-Item $fileToUpload
}

# Send file to cargo delivery endpoint using Invoke-RestMethod
try {
    $response = Invoke-RestMethod -Uri $endpoint -Method Post -Form $formData -TimeoutSec 60

    # Output response from server
    Write-Host "Server response: $($response.message)"
}
catch {
    Write-Host "Error occurred: $_"
}
