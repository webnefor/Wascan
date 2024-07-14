[𝐖𝐚𝐬𝐜𝐚𝐧]  

🅆eb 🄰pplication 🅂canner

This application is designed to scan web resources to identify open ports.

You can enter the range you want to start from using the -h parameter and enter the end of the range through a dash.

Also enter the desired ports using the -p option

To compile, type: 
    
    cmake CMakeLists.txt && make
    
Example:    

    ./wascan -p 80,443 -h 1.1.1.1-1.1.1.255
    
<img width="609" alt="Screenshot 2024-07-14 at 20 49 39" src="https://github.com/user-attachments/assets/60a35c84-e005-4e3d-a438-f1692315592c">
