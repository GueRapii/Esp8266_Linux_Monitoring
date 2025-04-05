import psutil
import time
from flask import Flask, jsonify
from datetime import timedelta

app = Flask(__name__)

prev_sent = psutil.net_io_counters().bytes_sent
prev_recv = psutil.net_io_counters().bytes_recv
prev_time = time.time()

def get_network_speed():
    global prev_sent, prev_recv, prev_time
    current_sent = psutil.net_io_counters().bytes_sent
    current_recv = psutil.net_io_counters().bytes_recv
    current_time = time.time()

    time_diff = current_time - prev_time
    sent_speed = ((current_sent - prev_sent) / 1024) / time_diff
    recv_speed = ((current_recv - prev_recv) / 1024) / time_diff

    prev_sent, prev_recv, prev_time = current_sent, current_recv, current_time

    return {"sent_speed": sent_speed, "recv_speed": recv_speed}

def get_cpu_temperature():
    try:
        temps = psutil.sensors_temperatures()
        if "coretemp" in temps:
            core_temps = [temp.current for temp in temps["coretemp"]]
            return sum(core_temps) / len(core_temps)
    except AttributeError:
        pass
    return None

def get_disk_usage():
    root = psutil.disk_usage("/")
    data = psutil.disk_usage("/mnt/data")
    
    return {
        "root_total": round(root.total / (1024**3), 2),
        "root_used": round(root.used / (1024**3), 2),
        "root_free": round(root.free / (1024**3), 2),
        "data_total": round(data.total / (1024**3), 2),
        "data_used": round(data.used / (1024**3), 2),
        "data_free": round(data.free / (1024**3), 2)
    }

def get_uptime():
    uptime_seconds = int(time.time() - psutil.boot_time())
    days = uptime_seconds // 86400
    time_part = str(timedelta(seconds=uptime_seconds % 86400))
    return f"{days}-{time_part}"

def format_ram(used, total):
    used_str = f"{used / 1024:.2f} GB" if used >= 1024 else f"{int(used)} MB"
    total_str = f"{total / 1024:.2f} GB" if total >= 1024 else f"{int(total)} MB"
    return f"{used_str}/{total_str}"

@app.route('/status')
def status():
    ram = psutil.virtual_memory()
    network = get_network_speed()
    
    return jsonify({
        "cpu": psutil.cpu_percent(),
        "ram": format_ram(ram.used / (1024**2), ram.total / (1024**2)),
        "temp": get_cpu_temperature() or "N/A",
        **get_disk_usage(),
        **network,
        "uptime": get_uptime()
    })

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)