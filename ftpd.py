from ftplib import FTP
import os

IP = "192.168.1.15"
PORT = 5000

tid = "00040000001A0300"

plg_dir = "/luma/plugins/"
plg_name = os.path.basename(os.path.dirname(__file__)) + ".3gx"

print("installing via ftpd ...")

with FTP() as ftpd:
    try:
        ftpd.connect(IP, PORT, timeout=60)

        ftpd.cwd(plg_dir)

        dlist = ftpd.nlst(".")
        for dir in dlist: 
            if(os.path.basename(dir) == tid): #if exist, rmd
                ftpd.cwd(tid)
                flist = ftpd.nlst(".")
                for f in flist:
                    ftpd.delete(f)
                
                ftpd.cwd(plg_dir)
                ftpd.rmd(tid)
    
        ftpd.mkd(tid)
        ftpd.cwd(tid)

        with open(plg_name, "rb") as plg:
            ftpd.storbinary(f"STOR {plg_name}", plg)
    finally:
        ftpd.close()