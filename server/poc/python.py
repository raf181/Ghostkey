from flask import Flask, request, jsonify

app = Flask(__name__)

# Store commands for each device
commands = {}

@app.route('/get_command', methods=['GET'])
def get_command():
    device_id = request.args.get('device_id')
    if device_id in commands:
        command = commands[device_id]
        del commands[device_id]  # Clear the command after sending
        return jsonify({'command': command})
    else:
        return jsonify({'command': None})

@app.route('/send_command', methods=['POST'])
def send_command():
    data = request.get_json()
    device_id = data['device_id']
    command = data['command']
    commands[device_id] = command
    return jsonify({'status': 'command sent'})

@app.route('/report_status', methods=['POST'])
def report_status():
    data = request.get_json()
    device_id = data['device_id']
    status = data['status']
    print(f"Device {device_id} reported: {status}")
    return jsonify({'status': 'status received'})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
