두개차이를 살펴 봤는데 설명하지니 좀 길어지네요 ..;;;  
일단 겉보기로는
기존 waypoint_follower는 목적지를 여러개 지정해주고 도착할때마다 도착하고 멈춤 하고 다음 출발 이런 식인데요.
이건 멈춤없이 해당 포인트들은 그냥 global path 경우지 처럼 거처 지나가는 것처럼 동작하는 것 같습니다.  

그런데 이게 코드 내부를 보면;;; 구현 방식이 완전히 틀린것 같습니다.  
waypoint_follower는 별도의 plubin 형태로 제작을 해서
https://github.com/ros-planning/navigation2/tree/navigate_through_poses/nav2_waypoint_follower
해당 플러그인을 호출하면 알아서 navigate_to_pose 액션을 앞에 액션이 성공한후 순차적으로 반복적으로 호출해 주는 형식이거든요.
그러니까 navigation 전체사이클에 해당하는 behavior tree가 사실상 찍은 골 포인트만큼 반복적으로 도는거고 당연히 목적기 골에 도착하는 중간중간 마다 멈춤이 나올수 밖에 없는형태고요.

그런데 이번에 새로 추가된것 같은 깃 푸쉬된지 24시간도 안된것 같습니다. ;;;;;
Navigate Through Poses 의 경우는 골을 여러번 찍어도 navigate_to_pose 액션은 한번만 호출하고  
navigate_to_pose 액션 실행시 호출되는 behavior tree xml를 수정한 방식인것 같습니다
https://github.com/ros-planning/navigation2/blob/navigate_through_poses/nav2_bt_navigator/behavior_trees/navigate_through_poses_w_replanning_and_recovery.xml
behavior tree에 RemovePassedGoals 라는 behavior tree action 을 추가해서 global path 도착이 성공하면 navigation  한사이클이 끝나는게 아니고 다음 global path 를 바로 생성해서 바로 이어서 따라가게 하는것 같네요 흠..
돌려보지는 Navigate Through Poses가 nav2 의 장점인 behavior tree 를 잘 활용한거 같긴하네요
일단 기본 기능이 점점 추가 되니까 좋긴 하네요  
