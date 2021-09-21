class Node:
  data = None
  next = None
  def __init__(self, _data=None):
    self.data = _data

class LinkedList:
  head = Node()

  def __init__(self):
    head = None

  def insert(self, data):
    _node = Node(data)
    if head == None:
      head == _node
    else:
      _node.next = head
      head = node
  
  def traverse(self):
    begin = self.head
    while begin != None:
      print(begin.data, sep=' ')
      begin = begin.next

if __name__ == '__main__':
  list = LinkedList()
  list.insert(8)
  list.insert(64)
  list.insert(2)
  list.insert(1)
  list.insert(32)
  list.insert(16)
  list.insert(4)