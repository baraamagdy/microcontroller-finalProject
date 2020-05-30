# microcontroller-finalProject
###Design Hotel-room’s door control board. Using TivaC board.
#####The designed control board shall lock and unlock a solenoid lock. The control board gets its inputs from the hotel
#####receptionist’s PC through UART or from the guest using keypad.
----------------------------------------------------------------------------
####Mode of operations: 
1) setup mode: from pc, enter the numbers of rooms you have
2) check-in: from pc send the number of room, its status and the password
3) cleaning room: from pc, send the number of room and the new status
*Now the room should be unlocked
3) check-out: from pc, send the number of the room and its status
*Now the room should be locked
**The number of room that you send is the one that has a connected keypad and lockw
