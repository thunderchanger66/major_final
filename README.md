# 分支説明
1.有幾個是測試的分支，主要分支就是repeatredo和main  
2.main分支是原來使用分區zigzag+A*的分支，效果一般  
3.repeatredo是改進貪心最近鄰和覆蓋率的分支，是現在做到的最好的效果  
4.現在主要使用repeatredo開發
# 參數説明
1.現在主要就是調整pathplan.cpp裏每行的跳數和間隔取點的距離，膨脹係數也能修改  
2.repeatredo分支中，貪心最近鄰計算距離的方案有兩個，一個是使用A*（因爲考慮到
要避障），還有一個是直接使用兩點的歐式距離，經測試，直接使用歐式距離效果還好一
些，使用A*還及其損耗資源，需要多綫程并行才能在一定忍耐時間内完成
# repeatredo貪心最近鄰方法思路如下
1.不需要分區zigzag，直接使用zigzag并且提前離散原始路徑點  
2.計算出每兩個路徑點之間的距離（現在使用歐式距離）  
3.從起點開始，尋找距離當前點最近的下一個點，放入新的路徑容器，重複，直至最後一個路徑點  
4.得到最新路徑后，還是需要用A*將這些路徑點連接起來，形成連續路徑
# 最新更新説明
1.對路徑點實現離散化，同時使用曲率特徵判定接近直綫的路徑點，直接跳過，減少點數
