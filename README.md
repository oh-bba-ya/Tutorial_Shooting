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
Skill : Space Bar


development explanation
-------------
## (1) Pawn Movement  
Unreal Engine에서 기존에 사용하던 Axis and Action mappings deprecated 될 예정이기 때문에 Enhanced Input을 통해 Movement를 구현했습니다.  

![01](https://user-images.githubusercontent.com/49023743/218031643-727fefb8-ac76-455f-92be-abed6d32b501.PNG)
![02](https://user-images.githubusercontent.com/49023743/218031797-976d894b-b945-427e-ac6a-1ca10d43c004.PNG)



## (2) Bullet  
Player가 Moust Left 클릭을 할때 Actor를 Spawn 발사하는 방식입니다.
player의 블루프린트 클래스 Details 패널에서 원하는 Count, Spacing, Angle을 입력한다면 입력에 따라 총알이 회전 및 추가되어 발사됩니다.  (Default Settings : Count = 1, Spacing = 150, bulletAngle = 30)  
![03](https://user-images.githubusercontent.com/49023743/218033283-acfbe319-76d6-485d-93c6-df25485930ab.PNG)
  
<img width="80%" src="https://user-images.githubusercontent.com/49023743/218135016-3dd397a6-d132-492b-bac1-aa42e1793d57.gif"/>



## (3) Enemy  
EnemySpawningPool 클래스를 통해 Enemy를 소환을 관리했습니다. Enemy의 경우 Actor Class로서 Player의 위치로 Enemy가 움직입니다.  
level에 배치된 BP_EnemySpawningPool 클래스를 통해 Enemy가 소환됩니다.  
![04](https://user-images.githubusercontent.com/49023743/218037009-092b78f0-2931-4991-8553-b7e07a86d274.PNG)




## (4) Widget  
- Score Widget의 경우 Game 시작시부터 Viewport에 생성되며 Player가 Enemy를 파괴할시에 Widget Animation을 통해 다음과 같이 Animation이 재생됩니다.  
![06](https://user-images.githubusercontent.com/49023743/218037809-2f0172f0-b851-4a7e-80e3-fb479017fed6.PNG)

<img width="80%" src="https://user-images.githubusercontent.com/49023743/218042679-25333dc1-a8e5-4d3a-a221-6b3ee22fa857.gif"/>


- Game Over Widget의 경우 Player가 파괴되었을시 Viewport에 추가가 됩니다.  

![05](https://user-images.githubusercontent.com/49023743/218037785-7cdb7c99-54d6-4a51-9840-69d250cf8a9a.PNG)



## (5) Skill  
Space Bar 키를 누름으로써 Enemy를 삭제시킬 수 있습니다. (Draw Debug로 그려지는 Sphere 범위 안에 있는 모든 Enemy를 파괴시킵니다.)  
<img width="80%" src="https://user-images.githubusercontent.com/49023743/218042736-51b4c1df-37db-4d0d-8849-c447bca8ef32.gif"/>  


  
  
## (6) Obstacle and Shield  
- 블랙홀안에서는 플레이어가 공격하지 못합니다. 블랙홀은 Random한 위치로 계속 옮겨집니다.  
<img width="80%" src="https://user-images.githubusercontent.com/49023743/218140419-642a4367-388f-4465-b8fc-1a234c87aa56.gif"/>  



- Shield의 경우 플레이어와 충돌할시 하위 액터로 부착되며 Enemy의 충돌을 막아주게 됩니다.
<img width="80%" src="https://user-images.githubusercontent.com/49023743/218140551-74955c83-cc69-4037-ab16-9e3b28c09a23.gif"/>  


