Shooting
=============
Project Info

인원 : 1명

기간 : 2022.12 ~ 2023.01

Tool : Unreal Engine 5.1 With C++


Description
-------------
Key Info

이동 : w,a,s,d  
공격 : Mouse Left Cilck  
Speed Up : Left Shift  



development explanation
-------------
(1) Pawn Movement  
Unreal Engine에서 기존에 사용하던 Axis and Action mappings deprecated 될 예정이기 때문에 Enhanced Input을 통해 Movement를 구현했습니다.  

![01](https://user-images.githubusercontent.com/49023743/218031643-727fefb8-ac76-455f-92be-abed6d32b501.PNG)
![02](https://user-images.githubusercontent.com/49023743/218031797-976d894b-b945-427e-ac6a-1ca10d43c004.PNG)



(2) Bullet  
Player가 Moust Left 클릭을 할때 Actor를 Spawn 발사하는 방식입니다.
player의 블루프린트 클래스 Details 패널에서 원하는 Count, Spacing, Angle을 입력한다면 입력에 따라 총알이 회전 및 추가되어 발사됩니다.  (Default Settings : Count = 1, Spacing = 150, bulletAngle = 30)
![03](https://user-images.githubusercontent.com/49023743/218033283-acfbe319-76d6-485d-93c6-df25485930ab.PNG)



(3) Enemy  
EnemySpawningPool 클래스를 통해 Enemy를 소환을 관리했습니다. Enemy의 경우 Actor Class로서 Player의 위치로 Enemy가 움직입니다.  
level에 배치된 BP_EnemySpawningPool 클래스를 통해 Enemy가 소환됩니다.  
![04](https://user-images.githubusercontent.com/49023743/218037009-092b78f0-2931-4991-8553-b7e07a86d274.PNG)


(4) Widget  
- Score Widget의 경우 Game 시작시부터 Viewport에 생성되며 Player가 Enemy를 파괴할시에 Widget Animation을 통해 다음과 같이 Animation이 재생됩니다.  




