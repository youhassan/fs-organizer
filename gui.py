import os
import subprocess
import tkinter as tk
from tkinter import filedialog, messagebox

def start_organizer():
    root = tk.Tk()
    root.withdraw() 
    folder_path = filedialog.askdirectory(title="Select A Folder")
    
    if not folder_path:
        return

    cpp_exe_path = "fs-organizer.exe" 
    
    if not os.path.exists(cpp_exe_path):
        messagebox.showerror("Error", f"Couldn't Find The C++ Executable: {cpp_exe_path}\nMake sure it's in the same folder.")
        return

    try:
        process = subprocess.Popen(
            [cpp_exe_path, folder_path],
            stdin=subprocess.PIPE,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            bufsize=1
        )

        final_output = []

        for line in iter(process.stdout.readline, ''):
            line_stripped = line.strip()
            
            if line_stripped.startswith("Confirm Delete:"):
                filepath = line_stripped.split(":", 1)[1]
                
                ans = messagebox.askyesno("Duplicate Found!", f"Found Duplicate File:\n{filepath}\n\nDo You Want To Delete It?")
                
                if ans:
                    process.stdin.write("y\n")
                else:
                    process.stdin.write("n\n")
                process.stdin.flush()
                
            else:
                if line_stripped:
                    final_output.append(line_stripped)

        process.wait()
        
        if process.returncode == 0:
            output_text = "\n".join(final_output)
            messagebox.showinfo("Done!", output_text)
        else:
            err = process.stderr.read()
            messagebox.showerror("C++ Error", err)

    except Exception as e:
        messagebox.showerror("Python Error", str(e))

if __name__ == "__main__":
    start_organizer()