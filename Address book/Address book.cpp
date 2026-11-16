//项目名称：简单的通讯录管理程序
//项目功能：实现通讯录的增删改查功能
#include <iostream>
#include <cstring> 
using namespace std;

//定义联系人结构体
struct Contact
{
    char name[50]; //联系人姓名
    char phone[12]; //联系人电话
    struct Birthday //联系人生日
    {
        int year; //年
        int month; //月
        int day; //日
    } birthday;
    int age; //联系人年龄
};

//定义通讯录结点结构体
struct Node
{
    Contact data; //联系人信息
    Node* next; //指向下一个结点的指针
};

/*函数功能：初始化一个空的通讯录链表
* 函数形参:无
* 函数返回值：返回一个空的通讯录链表头指针，Node*类型
*/
Node* InitAddressBook()
{
    Node* head = new Node; //创建一个新的结点（头结点）
    if (head == NULL) //判断是否创建成功
    {
        cout << "内存分配失败！" << endl;
        return NULL;
    }
    head->next = NULL; //将头结点的 next 指针置为空
    return head; //返回头结点指针
}

/*函数功能：采用头插法创建一个通讯录链表
* 函数形参：通讯录链表头指针 Node* head，联系人信息 Contact data
* 函数返回值：创建成功返回 true, 否则返回 false, bool 类型
*/
bool CreateAddressBookHead(Node* head, Contact data)
{
    Node* node = new Node; //创建一个新的结点
    if (node == NULL) //判断是否创建成功
    {
        cout << "内存分配失败！" << endl;
        return false; //创建失败返回 false
    }
    node->data = data; //将联系人信息赋值给新结点
    node->next = head->next; //将新结点的 next 指针指向头结点的下一个结点
    head->next = node; //将头结点的 next 指针指向新结点
    return true; //创建成功返回 true
}

/*函数功能：采用尾插法创建一个通讯录链表
* 函数形参：通讯录链表头指针 Node* head，联系人信息 Contact data
* 函数返回值：创建成功返回 true,否则返回 false, bool 类型
*/
bool CreateAddressBookTail(Node* head, Contact data)
{
    Node* node = new Node; //创建一个新的结点
    if (node == NULL) //判断是否创建成功
    {
        cout << "内存分配失败！" << endl;
        return false; //创建失败返回 false
    }
    node->data = data; //将联系人信息赋值给新结点
    node->next = NULL; //将新结点的 next 指针置为空

    // 每次从头开始找尾指针，避免使用 static 带来的隐藏 bug
    Node* tail = head;
    while (tail->next != NULL)
    {
        tail = tail->next;
    }
    tail->next = node; //将尾结点的 next 指针指向新结点
    return true; //创建成功返回 true
}

/*函数功能：输入单个联系人信息（带防死循环机制）
* 函数形参：无
* 函数返回值：返回联系人信息，Contact 类型
*/
Contact InputContact()
{
    Contact data;

    cout << "请输入联系人姓名: ";
    cin >> data.name;

    cout << "请输入联系人电话: ";
    cin >> data.phone;

    cout << "请输入联系人生日（年 月 日，用空格隔开）: ";
    // 防止输入字母导致 cin 崩溃死循环
    while (!(cin >> data.birthday.year >> data.birthday.month >> data.birthday.day))
    {
        cin.clear(); // 清除错误状态
        cin.ignore(1024, '\n'); // 清空缓冲区里的错误字符
        cout << "【输入错误】年月日必须是数字，请重新输入: ";
    }

    data.age = 2026 - data.birthday.year; //计算年龄
    return data;
}

/*函数功能：输出单个联系人信息
* 函数形参：联系人信息 Contact data
* 函数返回值：无，void 类型
*/
void OutputContact(Contact data)
{
    cout << "姓名: " << data.name << endl;
    cout << "电话: " << data.phone << endl;
    cout << "生日: " << data.birthday.year << "年" << data.birthday.month << "月" << data.birthday.day << "日" << endl;
    cout << "年龄: " << data.age << endl;
}

/*函数功能：输出通讯录中所有联系人信息
* 函数形参：通讯录链表头指针 Node* head
* 函数返回值：无，void 类型
*/
void OutputAddressBook(Node* head)
{
    Node* node = head->next;
    if (node == NULL)
    {
        cout << "通讯录为空！" << endl;
        return;
    }
    while (node)
    {
        OutputContact(node->data);
        cout << "------------------------" << endl;
        node = node->next;
    }
}

/*函数功能：按姓名查找通讯录中指定联系人信息
* 函数形参：通讯录链表头指针 Node* head，联系人姓名 char name[]
* 函数返回值：查找成功，返回地址，否则返回空，Node*类型
*/
Node* SearchContactByName(Node* head, char* name)
{
    Node* node = head->next;
    while (node)
    {
        if (strcmp(node->data.name, name) == 0)
            return node; //查找成功，返回结点地址
        node = node->next;
    }
    return NULL; //查找失败，返回空
}

/*函数功能：按电话查找通讯录中指定联系人信息
* 函数形参：通讯录链表头指针 Node* head，联系人电话 char phone[]
* 函数返回值：查找成功，返回地址，否则返回空，Node*类型
*/
Node* SearchContactByPhone(Node* head, char* phone)
{
    Node* node = head->next;
    while (node)
    {
        if (strcmp(node->data.phone, phone) == 0)
            return node; //查找成功，返回结点地址
        node = node->next;
    }
    return NULL; //查找失败，返回空
}

/*函数功能：在指定联系人的后面插入一个新的联系人
* 函数形参：通讯录链表头指针 Node* head，指定联系人地址 Node* target，联系人信息 Contact data
* 函数返回值：插入成功，返回 true，否则返回 false，bool 类型
*/
bool InsertContactAfter(Node* head, Node* target, Contact data)
{
    Node* node = new Node; //创建一个新的结点
    if (node)
    {
        node->data = data; //数据域赋值
        node->next = target->next; //指针域赋值
        target->next = node; //将指定结点的 next 指针指向新结点
        return true; //插入成功，返回 true
    }
    return false;
}

/*函数功能：查找指定联系人的前驱结点
* 函数形参：通讯录链表头指针 Node* head，指定联系人地址 Node* target
* 函数返回值：查找成功，返回前驱，否则返回空，Node*类型
*/
Node* SearchPreNode(Node* head, Node* target)
{
    for (Node* pre = head; pre->next != NULL; pre = pre->next)
    {
        if (pre->next == target)
            return pre; //查找成功，返回前驱结点地址
    }
    return NULL; //查找失败，返回空
}

/*函数功能：在指定联系人的前面插入一个新的联系人
* 函数形参：通讯录链表头指针 Node* head，指定联系人地址 Node* target，联系人信息 Contact data
* 函数返回值：插入成功，返回 true，否则返回 false，bool 类型
*/
bool InsertContactBefore(Node* head, Node* target, Contact data)
{
    Node* pre = SearchPreNode(head, target); //查找指定联系人的前驱结点
    if (pre) //查找成功
    {
        Node* node = new Node; //创建一个新的结点
        if (node)
        {
            node->data = data; //数据域赋值
            node->next = target; //指针域赋值
            pre->next = node; //将前驱结点的 next 指针指向新结点
            return true; //插入成功，返回 true
        }
    }
    return false; //插入失败，返回 false
}

/*函数功能：删除指定联系人
* 函数形参：通讯录链表头指针 Node* head，指定联系人 Node* target
* 函数返回值：删除成功，返回 true，否则返回 false，bool 类型
*/
bool DeleteContact(Node* head, Node* target)
{
    Node* pre = SearchPreNode(head, target); //查找指定联系人的前驱结点
    if (pre) //查找成功
    {
        pre->next = target->next; //将前驱结点的 next 指针指向指定结点的下一个结点
        delete target; //释放指定结点的内存空间
        return true; //删除成功，返回 true
    }
    return false; //删除失败，返回 false
}

/*函数功能：删除指定联系人的后继
* 函数形参：通讯录链表头指针 Node* head，指定联系人 Node* target
* 函数返回值：删除成功，返回 true，否则返回 false，bool 类型
*/
bool DeleteContactNext(Node* head, Node* target)
{
    if (target->next) //判断指定结点是否有后继结点
    {
        Node* node = target->next; //保存指定结点的后继结点
        target->next = node->next; //将指定结点的 next 指针指向后继结点的下一个结点
        delete node; //释放后继结点的内存空间
        return true; //删除成功，返回 true
    }
    return false; //删除失败，返回 false
}

/*函数功能：打印用户选择菜单（带防死循环机制）
* 函数形参：无
* 函数返回值：返回用户的选择，int 类型
*/
int PrintMenu()
{
    int choice;
    cout << "\n========== 通讯录管理程序 ==========" << endl;
    cout << "1. 添加联系人" << endl;
    cout << "2. 删除联系人" << endl;
    cout << "3. 查找联系人" << endl;
    cout << "4. 修改联系人" << endl;
    cout << "5. 显示所有联系人" << endl;
    cout << "6. 退出程序" << endl;
    cout << "请输入您的选择（1-6）：";

    // 防止输入字母导致无限死循环
    while (!(cin >> choice))
    {
        cin.clear(); // 清除错误状态
        cin.ignore(1024, '\n'); // 清空缓冲区
        cout << "【输入无效】请输入纯数字（1-6）：";
    }

    return choice;
}

// 主函数
int main()
{
    Node* head = InitAddressBook(); // 初始化带头结点的链表
    if (head == NULL) return 1;

    int choice;
    do
    {
        choice = PrintMenu();

        switch (choice)
        {
        case 1: // 添加联系人
        {
            Contact data = InputContact();
            if (CreateAddressBookTail(head, data)) // 使用尾插法，按输入顺序排列
                cout << "添加成功！" << endl;
            else
                cout << "添加失败！" << endl;
            break;
        }
        case 2: // 删除联系人
        {
            char name[50];
            cout << "请输入要删除的联系人姓名：";
            cin >> name;
            Node* target = SearchContactByName(head, name);
            if (target)
            {
                if (DeleteContact(head, target))
                    cout << "删除成功！" << endl;
                else
                    cout << "删除失败！" << endl;
            }
            else
            {
                cout << "未找到该联系人！" << endl;
            }
            break;
        }
        case 3: // 查找联系人
        {
            char name[50];
            cout << "请输入要查找的联系人姓名：";
            cin >> name;
            Node* target = SearchContactByName(head, name);
            if (target)
                OutputContact(target->data);
            else
                cout << "未找到该联系人！" << endl;
            break;
        }
        case 4: // 修改联系人
        {
            char name[50];
            cout << "请输入要修改的联系人姓名：";
            cin >> name;
            Node* target = SearchContactByName(head, name);
            if (target)
            {
                cout << "已找到该联系人，请输入新的信息：" << endl;
                target->data = InputContact(); // 重新录入信息覆盖原数据
                cout << "修改成功！" << endl;
            }
            else
            {
                cout << "未找到该联系人！" << endl;
            }
            break;
        }
        case 5: // 显示所有联系人
        {
            OutputAddressBook(head);
            break;
        }
        case 6: // 退出程序
        {
            cout << "感谢使用，程序退出！" << endl;
            break;
        }
        default:
        {
            cout << "输入无效，请输入 1-6 之间的数字！" << endl;
            break;
        }
        }
    } while (choice != 6);

    // 程序结束前，释放整个链表，防止内存泄漏
    Node* p = head;
    while (p != NULL)
    {
        Node* q = p->next;
        delete p;
        p = q;
    }

    return 0;
}