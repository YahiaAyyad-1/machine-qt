#!/usr/bin/env python3.6
import sys
from xmlrpc.client import ServerProxy

def main(args):
    server = ServerProxy('http://10.2.0.202:9001/RPC2')
    request = args[0]
    allProcInfo = server.supervisor.getAllProcessInfo()
    services = [{"name": proc["name"], "state": proc["statename"]} for proc in allProcInfo]
    if request == "-getData":
        print(services)
    elif request == "-getServicesInfo":
        info = []
        for service in args[1:]:
            proc = server.supervisor.getProcessInfo(service)
            info.append({"name": proc["name"], "state": proc["statename"]})
        print(info)
    elif request == "-restart":
        srvName = args[1]
        srvStatus = None
        for srv in services:
            if srv["name"] == srvName:
                srvStatus = srv["state"]
                break
        if srvStatus == "STOPPED":
            server.supervisor.startProcess(srvName)
        elif srvStatus == "RUNNING":
            server.supervisor.stopProcess(srvName)
            server.supervisor.startProcess(srvName)
    elif request == "-start":
        srvName = args[1]
        server.supervisor.startProcess(srvName)
    elif request == "-stop":
        srvName = args[1]
        server.supervisor.stopProcess(srvName)

if __name__ == '__main__':
    args = sys.argv[1:]
    main(args)
