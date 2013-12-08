import subprocess
import string as s

class battery():
    def __init__(self,OS="LINUX",VERBOSE=False):
        self.OS = OS
        self.verbose = VERBOSE
    
    def getMaxBatLevel(self):
        if self.OS == "LINUX":
            proc = subprocess.check_output(["acpi -V | grep 'design capacity'"],stderr=subprocess.STDOUT,shell=True)
        elif self.OS == "MAC":
            proc = subprocess.check_output(['ioreg -w0 -l | grep MaxCapacity'],stderr=subprocess.STDOUT,shell=True)
        if self.verbose:
            print proc
        return float([int(l) for l in proc.replace("%"," ").split() if l.isdigit()][0])

    def getCurBatLevel(self):
        if self.OS == "LINUX":
            try:
                proc = subprocess.check_output(['acpi -V | grep Discharging'],stderr=subprocess.STDOUT,shell=True)
            except subprocess.CalledProcessError:
                # Battery not discharging. Check if charging.
                try:
                    proc = subprocess.check_output(['acpi -V | grep Charging'],stderr=subprocess.STDOUT,shell=True)
                except subprocess.CalledProcessError:
                    # Battery not charging either, check if full
                    try:
                        proc = subprocess.check_output(['acpi -V | grep Full'],stderr=subprocess.STDOUT,shell=True)
                    except subprocess.CalledProcessError:
                        raise NameError('BatError')
        elif self.OS == "MAC":
            proc = subprocess.check_output(['ioreg -w0 -l | grep CurrentCapacity'],stderr=subprocess.STDOUT,shell=True)
        if self.verbose:
            print proc
        # if on linux, this will return a percentage value, not a mAh value
        return float([int(l) for l in proc.replace("%"," ").split() if l.isdigit()][0])

    def getBatPercentage(self):
        if self.OS == "LINUX":
            return self.getCurBatLevel()
        elif self.OS == "MAC":
            return self.getCurBatLevel()/self.getMaxBatLevel()*100.0

    def isPlugged(self):
        if self.OS == "LINUX":
            proc = subprocess.check_output(['acpi -V | grep line'],stderr=subprocess.STDOUT,shell=True)
            if self.verbose:
                print proc
            return "on" in proc.lower().replace("-"," ").split()
        elif self.OS == "MAC":
            proc = subprocess.check_output(['ioreg -w0 -l | grep ExternalChargeCapable'],stderr=subprocess.STDOUT,shell=True)
            if self.verbose:
                print proc
            return "yes" in proc.lower().split()

    def batteryState(self):
        if self.OS == "LINUX":
            try:
                proc = subprocess.check_output(['acpi -V | grep Discharging'],stderr=subprocess.STDOUT,shell=True)
            except subprocess.CalledProcessError:
                # Battery not Charging, check if charging
                try:
                    proc = subprocess.check_output(['acpi -V | grep Charging'],stderr=subprocess.STDOUT,shell=True)
                except subprocess.CalledProcessError:
                # Battery not charging either, check if full
                    try:
                        proc = subprocess.check_output(['acpi -V | grep Full'],stderr=subprocess.STDOUT,shell=True)
                    except subprocess.CalledProcessError:
                        raise NameError('BatError')
            return "Charging" if proc.find("Charging") else "Discharging"
        elif self.OS == "MAC":
            return "Charging" if self.isPlugged() else "Discharging"

    def debugClass(self):
        print "Max level ", getMaxBatLevel()
        print "Current level ", getCurBatLevel()
        print "Level pecentage ", getBatPercentage()
        print "Charger plugged ", isPlugged()
