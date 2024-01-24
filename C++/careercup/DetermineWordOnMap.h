#include "../header.h"

/*
https://careercup.com/question?id=16142677

Given an virtual 4x4 boggle board, and some 4 letter words, determine if the words are in the board
ex.

S M E F
R A T D
L O N I
K A F B

STAR- no
TONE- no
NOTE- yes
SAND- yes
etc.


I think the other solutions do not handle usage of the same character twice. Below is the bug free solution.


def preProcessBoard(board):
    sz = len(board)
    boardMap = {}
    for i in xrange(sz):
        for j in xrange(sz):
            if board[i][j] in boardMap:
                boardMap[board[i][j]].append(i*sz+j)
            else:
                boardMap[board[i][j]] = [i*sz+j]
    return boardMap

def getNeighbors(index,sz):
    row = index/sz
    col = index % sz
    neigs = set()
    for i in xrange(row-1,row+2):
        for j in xrange(col-1,col+2):
            if i >=0 and i<sz and j>=0 and j<sz and not (i == row and j == col):
                neigs.add(i*sz+j)
    return neigs

def isOnBoard(boardMap,word,oldPos,posList):
    if len(word) == 0:
        return True
    if word[0] not in boardMap:
        return False
    else:
        if oldPos == None:
            for pos in boardMap[word[0]]:
                posList.add(pos)
                if isOnBoard(boardMap,word[1:],pos,posList):
                    return True
                else:
                    posList.remove(pos)
        else:
            for pos in boardMap[word[0]]:
                if pos in getNeighbors(oldPos,4) and pos not in posList:
                    posList.add(pos)
                    if isOnBoard(boardMap,word[1:],pos,posList):
                        return True
                    else:
                        posList.remove(pos)
    return False

board = [['s','m','e','f'],['r','a','t','d'],['l','o','n','i'],['k','a','f','b']]
boardMap = preProcessBoard(board)
print isOnBoard(boardMap,'afna',None,set())
*/
class DetermineWordOnMap {
};