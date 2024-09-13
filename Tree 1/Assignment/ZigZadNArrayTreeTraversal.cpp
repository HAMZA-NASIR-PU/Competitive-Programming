#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class TreeNode
{
public:
    int val;
    vector<TreeNode *> child;

    TreeNode(int val)
    {
        this->val = val;
    }

    ~TreeNode()
    {
        for (int i = 0; i < child.size(); i++)
        {
            delete child[i];
        }
    }
};

vector<int> zigzagLevelOrder(int n, TreeNode *root)
{
    vector<int> result;
    if (root == nullptr)
        return result;

    queue<TreeNode *> q;
    q.push(root);
    bool leftToRight = true;

    while (!q.empty())
    {
        int levelSize = q.size();
        deque<int> levelValues;

        for (int i = 0; i < levelSize; ++i)
        {
            TreeNode *node = q.front();
            q.pop();

            if (leftToRight)
            {
                levelValues.push_back(node->val);
            }
            else
            {
                levelValues.push_front(node->val);
            }

            for (TreeNode *child : node->child)
            {
                q.push(child);
            }
        }

        result.insert(result.end(), levelValues.begin(), levelValues.end());
        leftToRight = !leftToRight;
    }

    return result;
}

class Runner
{
    int t;
    vector<TreeNode *> allTree;
    vector<int> tn;

    TreeNode *takeNTreeInput()
    {

        int rootData;
        cin >> rootData;

        if (rootData == -1)
        {
            return NULL;
        }

        TreeNode *root = new TreeNode(rootData);

        queue<TreeNode *> q;
        q.push(root);

        while (q.empty() == false)
        {
            TreeNode *currentNode = q.front();
            q.pop();
            int insChild;

            cin >> insChild;

            while (insChild != -1)
            {
                TreeNode *newNode = new TreeNode(insChild);

                (currentNode->child).push_back(newNode);
                q.push(newNode);

                cin >> insChild;
            }
        }

        return root;
    }

    TreeNode *copyNTree(TreeNode *root)
    {
        if (root == NULL)
        {
            return NULL;
        }
        TreeNode *copyRoot = new TreeNode(root->val);
        for (int i = 0; i < (root->child).size(); i++)
        {
            TreeNode *copyChild = copyNTree(root->child[i]);
            (copyRoot->child).push_back(copyChild);
        }
        return copyRoot;
    }

public:
    void takeInput()
    {
        cin >> t;

        allTree.resize(t);

        for (int i = 0; i < t; i++)
        {
            int n;
            cin >> n;
            allTree[i] = takeNTreeInput();
            tn.push_back(n);
        }
    }

    void execute()
    {
        for (int i = 0; i < t; i++)
        {
            TreeNode *copyRoot = copyNTree(allTree[i]);

            vector<int> ans = zigzagLevelOrder(tn[i], copyRoot);
            delete copyRoot;
        }
    }

    void executeAndPrintOutput()
    {
        for (int i = 0; i < t; i++)
        {
            vector<int> ans = zigzagLevelOrder(tn[i], allTree[i]);
            for (int j : ans)
            {
                cout << j << " ";
            }
            cout << endl;
        }
    }
};

int main()
{

    Runner runner;
    runner.takeInput();
    runner.executeAndPrintOutput();

    return 0;
}