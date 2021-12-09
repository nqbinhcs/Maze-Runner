09/12/2021
@Binh
+ Thay đổi class Square -> MazeObject bao gồm file hpp, cpp
+ Tạo class Room (thay thế Cell) -> Chỉ mới tạo hpp
+ Tạo class MazeFactory, MazeCreationInterface

- Có nhiều phần cài đặt trong code mình chưa sử dụng cách tạo đổi tượng bằng MazeCreationInterface. Các ông nếu thấy phần code nào chưa áp dụng thì sửa nha
- Có nên sài shared pointer hết không getter đến setter ? Mấy ông giúp tui nghen, chứ ngu wa hic ;-;

@Thai: Cài đặt và thay đổi các lớp TileMap, Cell -> Maze, Room (Theo UML)
@Phuc: Đảm bảo chạy được phần running Game và refactor nếu cần

Yêu cầu: Thay đổi lại nhưng code vẫn chạy được như ban đầu


Push code: Để đảm bảo respo mình nhẹ, khi add thì các ông add những cái cần thiết nha. Như ai lỡ add hết, thì sử dụng [git rm] để xóa cái thư mục [.vs/MazeRunnerGame/ipch] nha
