import os
import time
import subprocess as process

def autoCommit() -> None:
    process.run(['git', 'status'],
                capture_output=True,
                text=True,
                check=True)
    
    time.sleep(1)
