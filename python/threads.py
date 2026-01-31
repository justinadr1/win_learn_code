import threading
import time

def task(n):
    print(f"Starting Task: {n}")
    time.sleep(1)
    print(f"Finishing Task: {n}")


threads = []

for i in range(1, 6):
    t = threading.Thread(target=task, args=(i,))
    threads.append(t)
    t.start()

for t in threads:
    t.join()