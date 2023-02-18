#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

struct Node
{
    string data;
    Node *next;
};

class TextEditor
{
private:
    Node *head;
    Node *tail;
    Node *current;
    Node *previous;
    Node *copy;

public:
    stack<Node *> un;
    stack<Node *> re;
    TextEditor()
    {
        head = NULL;
        tail = NULL;
        current = NULL;
        previous = NULL;
    }

    void insert(string data)
    {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = NULL;
        un.push(copyList(head));
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
            current = newNode;
        }
        else
        {
            newNode->next = current->next;
            current->next = newNode;
            previous = current;
            current = newNode;
            if (newNode->next == NULL)
            {
                tail = newNode;
            }
        }
    }

    void update(string index, string data)
    {
        Node *temp = head;
        un.push(copyList(head));
        while (temp != NULL)
        {
            if (temp->data == index)
            {
                current = temp;
                break;
            }
            temp = temp->next;
        }
        temp->data = data;
    }

    Node *copyList(struct Node *head)
    {
        // Write your code here
        Node *copy = NULL;
        Node *t = NULL;
        Node *temp = head;
        while (temp != NULL)
        {
            if (copy == NULL)
            {
                Node *ptr = new Node();
                ptr->data = temp->data;
                ptr->next = NULL;
                copy = ptr;
                t = copy;
            }
            else
            {
                Node *ptr = new Node();
                ptr->data = temp->data;
                ptr->next = NULL;
                t->next = ptr;
                t = t->next;
            }
            temp = temp->next;
        }
        return copy;
    }

    void append(string data)
    {
        Node *newNode = new Node;
        newNode->data = data;
        newNode->next = NULL;
        un.push(copyList(head));

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
            current = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
            previous = current;
            current = newNode;
        }
    }

    bool search(string data)
    {
        Node *temp = head;
        while (temp != NULL)
        {
            if (temp->data == data)
            {
                current = temp;
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    bool deleteData(string data)
    {
        un.push(copyList(head));
        Node *temp = head;
        Node *prev = NULL;

        while (temp != NULL)
        {
            if (temp->data == data)
            {
                if (temp == head)
                {
                    head = temp->next;
                }
                else
                {
                    prev->next = temp->next;
                }
                delete temp;
                return true;
            }
            prev = temp;
            temp = temp->next;
        }

        return false;
    }

    void display()
    {
        Node *temp = head;
        while (temp != NULL)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    void undo()
    {
        if (!un.empty())
        {
            re.push(head);
            head = un.top();
            un.pop();
        }
        else
        {
            cout << "Error: No undo available" << endl;
        }
    }

    void redo()
    {
        if (!re.empty())
        {
            un.push(head);
            head = re.top();
            re.pop();
        }
        else
        {
            cout << "Error: No undo available" << endl;
        }
    }

    void save(string fileName)
    {
        ofstream file(fileName);
        Node *temp = head;
        while (temp != NULL)
        {
            file << temp->data << endl;
            temp = temp->next;
        }
        file.close();
    }
};

int main()
{
    TextEditor editor;
    string input, fileName;
    int choice;

    do
    {
        cout << "Text Editor Menu\n";
        cout << "1. Insert\n";
        cout << "2. Update\n";
        cout << "3. Append\n";
        cout << "4. Search\n";
        cout << "5. Delete\n";
        cout << "6. Display\n";
        cout << "7. Undo\n";
        cout << "8. Redo\n";
        cout << "9. Save\n";
        cout << "0. Exit\n";
        cout << "Input Choice:";
        cin >> choice;
        cin.ignore();
        if (choice == 1)
        {
            cout << "Insert data:";
            string s;
            cin >> s;
            editor.insert(s);
            cout << "Inserted" << endl;
        }
        else if (choice == 2)
        {
            editor.display();
            cout << "Enter word:";
            string index, line;
            cin >> index;
            if (editor.search(index))
            {
                cout << "Enter new word:";
                cin >> line;
                editor.update(index, line);
                cout << "Updated" << endl;
            }
            else
            {
                cout << "Not Found" << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "Enter data:";
            string line;
            cin >> line;
            editor.append(line);
            cout << "Appended" << endl;
        }
        else if (choice == 4)
        {

            editor.display();
            cout << "Enter word:";
            string index;
            cin >> index;
            if (editor.search(index))
            {
                cout << "Data Found" << endl;
            }
            else
            {
                cout << "Data Not Found" << endl;
            }
        }
        else if (choice == 5)
        {

            editor.display();
            cout << "Enter word:";
            string line;
            cin >> line;
            if (editor.deleteData(line))
            {
                cout << "Data deleted" << endl;
            }
            else
            {
                cout << "Not Found" << endl;
            }
        }
        else if (choice == 6)
        {

            editor.display();
        }
        else if (choice == 7)
        {

            editor.undo();
            cout << "Undo Succesful" << endl;
        }
        else if (choice == 8)
        {

            editor.redo();
            cout << "Redo Succesful" << endl;
        }
        else if (choice == 9)
        {

            cout << "Enter file name: ";
            string name;
            cin >> name;
            editor.save(name);
            cout << "Data saved succesfully" << endl;
        }
        else
        {
            break;
        }
    } while (true);
}
