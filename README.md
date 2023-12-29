# DatasturctureHW3
作業目標：比較sorted array、array of sorted arrays、skip list的range query所需時間。

實作以下3個function:

	range_query:
 
  	input: 兩個正整數a和b。
   
  	output: 資料結構中所有介於a和b（大於等於a且小於等於b）的資料。這些資料須存放在一個multiset中（multiset的實作不限，如array或linked list）。
   
	equivalent:
 
  	input: 兩個multisets S_1與S_2。
   
  	output: yes if  S_1和S_2有相同元素，而且每個元素在S_1出現的次數等於該元素在S_2出現的次數；no otherwise。
   
  print:
  
	  input: 一個multisets S。在stdout輸出S的內容。
   
實驗步驟：

  Create data structure:
  
    Sorted array – for n times random create numbers then quicksort sort
    
    Array of sorted array – insert n times with random numbers
    
                            Arrs and temps use two arrays store their starting points
                            
                            Initial state is one arr and one temp each with one space
                            
                            Insert using recursive call, insert (array to be insert: initial size = 1, temp layer: 0~?) no return value
                            
                            Move temp to arr or opposite must move all, so check empty we only have to check one element of the array
  
    Skip list – create nodes that store up down left and right
  
             (search bottom position: use while + insert after confirm) function
  
    range_query function for three ds:
  
    equivalent function: 利用set存查到的query，有助於比對
	
   n=2^20-1,k=2^0,2^1,2^2,…,2^20 (可視電腦執行速度調整n與k的值) 
  	
   產生n個數，每個數字都從0~n-1隨機產生（每個數字被選到的機率都是1/n）。
  	
   將上述n個數存在檔案中，每行存一個數字。
  	
   讀檔並將n個數存入三個資料結構中。
  	
   隨機從0~n-1產生a（每個數字被選到的機率都是1/n）。
  	
   在三個資料結構執行range_query(a,a+k)，並測量時間。
  	
   利用equivalent檢查range_query結果是否一致。

繳交報告內容： 

 (30%)  一張折線圖（每張圖3條線，對應到上述3個資料結構range query執行時間）與實驗解釋
 
            x軸為k值：k=2^0,2^1,…,2^20。
            y軸為每個資料結構range query執行時間（產生10個input後取平均）。
         
         程式碼檔案，以上檔案壓縮後上傳moodle

Demo：

 (20%)  code 解釋

 (50%)  正確性測試：助教會提供多個測試檔案與range query的範圍，檢查range_query與equivalent是否正確
