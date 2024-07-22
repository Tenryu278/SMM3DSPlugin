from ftplib import FTP
import os

# Read IP address and port from "IP_PORT.txt"

# line1: Write your IP address
# line2: Write your Port number
# ---------Example---------
# 192.168.1.15
# 5000
# -------------------------
with(open("IP_PORT.txt")) as f:
    IP = f.readline().strip('\n')
    PORT = int(f.readline())

tid = "00040000001A0300"

plg_dir = "/luma/plugins/"
plg_name = os.path.basename(os.path.dirname(__file__)) + ".3gx"

print("installing via ftpd ...")

with FTP() as ftpd:
    try:
        ftpd.connect(IP, PORT, timeout=60)

        ftpd.cwd(plg_dir)

        dlist = ftpd.nlst(".")
        for di in range(len(dlist)): 
            dlist[di] = os.path.basename(dlist[di])
        
        if(tid in dlist):
            ftpd.cwd(tid)
            flist = ftpd.nlst(".")
            if(plg_name in flist):
                ftpd.delete(plg_name)
            if("CTRPFData.bin" in flist):
                ftpd.delete("CTRPFData.bin")
                
            ftpd.cwd("..")

        else:
            ftpd.mkd(tid)
        
        ftpd.cwd(tid)

        with open(plg_name, "rb") as plg:
            ftpd.storbinary(f"STOR {plg_name}", plg)
    finally:
        ftpd.close()