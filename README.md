# Credere
- 타이틀: Credere  
- 개발기간: 23'06'21 ~ 진행중  
- 개발목표: 고퀄리티 싱글플레이 RPG  
- 엔진버전: Unreal 5.2.1  
- 버전관리: git, git lfs  


# Project Build

1. 프로젝트 클론 or 다운로드(Git LFS Bandwidth초과로 clone이 불가능 할 경우 다운로드 링크 이용부탁드립니다)
```
git clone --depth 1 https://github.com/yuntaewoong/DirectX12_DXR_Renderer.git
```
[다운로드 링크(15.62GB)](https://15ywt.synology.me/sharing/qi4bVQLF3)  

2. `Credere.uproject` 우측 마우스 클릭
3. `Generate VisualStudio Project Files` 클릭
4. `Credere.sln` 클릭
5. `Credere`프로젝트 빌드
6. `Credere.uproject` 실행

# 조작법
`w`,`a`,`s`,`d` : 캐릭터 이동  
`q`,`e` : 조작 캐릭터 전환  
`space bar` : 점프  
`mouse X`, `mouse Y` : 시점 조작

# 개발 타임라인
- 23'06'21 ~ 23'06'22 : c++ 개발환경 세팅
- 23'06'26 ~ 23'06'30 : 조작 캐릭터 애샛(paragon 무료 애샛), c++로직 추가
- 23'07'07 ~ 23'07'11 : 맵 애샛(Infinity 무료 애샛), 테스트 맵 추가
- 23'07'18 ~ 23'07'25 : 네비게이션 개발
- 23'07'26 ~ 23'08'02 : 동료 캐릭터 시스템 개발(동료 AI, 조작 전환)
- 23'08'03 ~ 23'08'10 : 자체 스킬,스탯 시스템 개발시도(Gameplay Abillity System알게 된 후에 개발 중단)
- 23'08'11 ~ 23'08'13 : 언리얼 공식 Lyra스타터 프로젝트를 통해 GAS공부
- 23'08'14 ~ 23'08'23 : Gameplay Ability System으로 자동공격 체계 구현



# 주요 기능
## Navigation
(네비게이션 실시간 반영 움짤)   
구현 방법: 언리얼 엔진의 `UNavigationSystemV1`기능을 이용해서 구현.  
NavMesh를 비실시간 빌드한 후에 `UNavigationSystemV1`으로부터 시작점,종착점까지의 경로 Point배열을 얻어온 후에 Spline Mesh들로 경로를 시각화 한다.

 
## 조작 캐릭터 전환
(계속 움직이면서 캐릭터 조작 변경하는 움짤)  

구현 방법: 게임 시작 시 플레이어 조작을 반영하는 `AHumanPlayerController` 1개와  
동료 캐릭터 수만큼의 `APartnerAIController`를 스폰.  
게임인스턴스 서브시스템을 상속받는 `UPlayableCharacterSubsystem`에서 현재 조작할 수 있는 캐릭터 배열, 조작하고 있는 캐릭터를 관리하도록 구현.  
플레이어가 `q`,`e`인풋을 주면 `UPlayableCharacterSubsystem` 멤버함수를 호출해서 현재 AIController가 조작중인 동료 캐릭터를 possess하고 현재 캐릭터는 남는 AI Controller가 possess하는 로직 실행   

## Gameplay Ability System
(Health 디버깅하면서 자동공격하는 움짤)  
자동공격 Ability 구현 방법: 
1. AutoAttack GameplayAbility 클래스 생성
2. Health Attribute Set 클래스 생성
3. 캐릭터,적 base클래스에 AbilitySystemComponent 서브 오브젝트 생성 + Health Attribute Set 서브오브젝트 생성  
4. AutoAttack GameplayAbility의 ActivateAbility함수 구현(UAbilityTask_Repeat를 이용해서 반복 공격 구현)
5. ActivateAbility함수에서 사용할 GameplayEffect 블루프린트 생성
6. 자동공격함수 호출할때마다 ApplyGameplayEffectToTarget 함수로 GameplayEffect효과 발동

