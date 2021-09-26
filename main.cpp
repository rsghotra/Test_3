#include <iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<queue>
using namespace std;

struct ListNode {
  ListNode* next;
  int data;
  ListNode(int data) {
    this->data = data;
    this->next = 0;
  }
};

string SmallestSubstring(const string& str, const string& pattern) {
  unordered_map<char, int> frequencies;
  for(char ch: pattern) {
    frequencies[ch]++;
  }
  int windowStart = 0;
  int minLength = INT32_MAX;
  int startIndex = -1;
  int matchCount = 0;
  for(int windowEnd = 0; windowEnd < str.size(); windowEnd++) {
    if(frequencies.find(str[windowEnd]) != frequencies.end()) {
      frequencies[str[windowEnd]]--;
      if(frequencies[str[windowEnd]] >= 0) {
        matchCount++; //we will increase matchcount for every match
      }
    }

    while(matchCount == pattern.size()) {
      if(windowEnd - windowStart + 1 < minLength) {
        minLength = windowEnd - windowStart + 1;
        startIndex = windowStart;
      }
      if(frequencies.find(str[windowStart]) != frequencies.end()) {
        if(frequencies[str[windowStart]] == 0) {
          matchCount--;
        }
        frequencies[str[windowStart]]++;
      }
      windowStart++;
    }
  }
  return minLength > str.size() ? "": str.substr(startIndex, minLength);
}

void SmallestSubstring() {
  cout << "Smallest Substring" <<endl;
  cout << SmallestSubstring("aabdec", "abc") << endl;
}


int FindNextIndex(const vector<int>& nums, bool isForward, int currentIndex) {
  bool direction = nums[currentIndex] >= 0;
  //direction check
  if(direction != isForward) {
    return -1;
  }

  //wrapping
  int nextIndex = (currentIndex + nums[currentIndex])%nums.size();
  if(nextIndex < 0) {
    nextIndex = nextIndex + nums.size();
  }

  //1-element cycle
  if(nextIndex == currentIndex) {
    return -1;
  }
  return nextIndex;
}

//https://www.educative.io/courses/grokking-the-coding-interview/NE67J9YMj3m
bool DetectCycle(const vector<int>& nums) {
  for(int i = 0; i < nums[i]; i++) {
    bool isForward = nums[i] >= 0;
    int slow = i;
    int fast = i;
    do {
      slow = FindNextIndex(nums, isForward, slow);
      fast = FindNextIndex(nums, isForward, fast);
      if(fast != -1) {
        fast = FindNextIndex(nums, isForward, fast);
      }
    } while(slow != -1 && fast != -1 && slow != fast);

    if(slow == fast && slow != -1) {
      return true;
    }
  }
  return false;
}

void DetectCycle() {
  cout << "Array has cycle ? " << DetectCycle(vector<int>{1, 2, -1, 2, 2}) << endl;
}


//Modified Binary Search

int SmallestSubarrayLength(const vector<int>& nums) {
  int left = 0;
  int right = nums.size() - 1;
  while(left < nums.size() - 1 && nums[left] < nums[left+1]) {
    left++;
  }
  while(right > 0 && nums[right - 1] < nums[right]) {
    right--;
  }
  cout << "Left found at: " << left << endl;
  cout << "Right found at: " << right << endl;

  //find max and min from the found range;
  int minFound = INT32_MAX;
  int maxFound = INT32_MIN;

  for(int i = left; i <= right; i++) {
    minFound = min(minFound, nums[i]);
    maxFound = max(maxFound, nums[i]);
  }

  while(left > 0 && nums[left-1] > minFound) {
    left--;
  }

  while(right < nums.size() - 1 && nums[right+1] < maxFound) {
    right++;
  }
  cout << "Left found at: " << left << endl;
  cout << "Right found at: " << right << endl;
  return right - left + 1;
}


void SmallestSubarrayLength() {
  cout << "Smallest Subarray Length is: " << SmallestSubarrayLength(vector<int>{1, 2, -1, 2, 2}) << endl;
}


ListNode* ReverseAlternatingK(ListNode* head, int K) {
  //no need to take the position as we are alread here;
  ListNode* previous = 0;
  ListNode* current = head;

  while(current != 0) {
    ListNode* lastPrevious = previous;
    ListNode* lastCurrent = current;
    for(int i = 0; i < K && current != 0; i++) {
      ListNode* next = current->next;
      current->next = previous;
      previous = current;
      current = next;
    }
    if(lastPrevious) {
      lastPrevious->next = previous;
    } else {
      head = previous;
    }
    lastCurrent->next = current;
    //here MUST be BREAK only after setting down previous business
    if(current == 0) {
      head = previous;
      break;
    }
    previous = lastCurrent;
    for(int j = 0; j < K && current != 0; j++) {
      previous = current;
      current = current->next;
    }
  }
  return head;
}

void ReverseAlternatingK() {
  ListNode *head = new ListNode(1);
  head->next = new ListNode(2);
  head->next->next = new ListNode(3);
  head->next->next->next = new ListNode(4);
  head->next->next->next->next = new ListNode(5);
  head->next->next->next->next->next = new ListNode(6);
  head->next->next->next->next->next->next = new ListNode(7);
  head->next->next->next->next->next->next->next = new ListNode(8);

  ListNode *result = ReverseAlternatingK(head, 2);
  cout << "Nodes of the reversed LinkedList are: ";
  while (result != nullptr) {
    cout << result->data << " ";
    result = result->next;
  }
}

int main() {
  SmallestSubstring();
  DetectCycle();
  //EmployeeFreeTime
  SmallestSubarrayLength();
  ReverseAlternatingK();
  return 0;
}