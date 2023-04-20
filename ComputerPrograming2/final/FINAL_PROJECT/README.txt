# bang

## 流程

### 選擇角色

-  Paul Regret - 其他玩家看他的距離+1。他仍然可以再裝備【野馬】，裝備後距離共+2。
-  Rose Doolan - 看別的玩家的距離-1。他仍然可以裝備【瞄準器】，裝備後看其他玩家距離-2。

### 開始階段前

-  監獄(Jail) - 可以無視距離丟給任何一個玩家。當玩家收到這張牌時，將此牌當作裝備放在桌面上，當作進監獄，輪到該玩家時，抽一張牌，如果是紅心，則可以繼續他的回合，如果不是紅心，則跳過他的回合，判定後【監獄】牌可以丟棄。
-  炸彈(Dynamite) - 使用此牌時，要先裝備在自己的桌面上，這一回合並沒有效果，當下一輪回合到自己時，炸彈效果才會開始發動。
  
  當炸彈開始發動效果時，必須再抽牌階段前抽一張牌當作炸彈的判定：

  - 如果抽牌的花色和數字在炸彈範圍內，持有【炸彈】的玩家被扣3滴血，沒死的話繼續自己的回合
  - 如果不再範圍內，將炸彈給左邊的玩家，並開始自己的回合

### 抽排階段

  抽2張牌，沒牌就洗牌

-  Black Jack - 在抽牌階段，必須亮出抽出的第二張牌，若該牌是紅心或方塊，他可以再多抽一張牌
-  Jesse Jones - 在抽牌階段時，第一張牌可以選擇從遊戲牌堆中或是任一位玩家的手牌中抽牌。第二張則是從遊戲牌中抽牌。
-  Kit Carison - 抽牌階段時，可以從遊戲牌堆上方拿三張起來看，選擇兩張，放回一張到遊戲牌堆頂端。
-  Pedro Ramirez -在抽牌階段時，第一張牌可以選擇從棄牌堆或遊戲牌堆中抽牌，第二張牌只能從遊戲牌中抽牌。

### 出牌階段

  bang只能出一張 (先檢查可連發 or bang第二次的時候檢查)   
  裝備檢查 (只能一個武器 一隻馬 卡片都存在一張)   
  檢查射程 (如果是A要打B 計算 B(+1) - A(-1) + A武器射程(預設1) >= A到B距離)   

-  Bart Cassidy - 被扣一滴血時，可以從卡牌堆中抽一張牌
-  Calamity Janet - 遊戲牌中的【閃躲】可以當【Bang】用；【Bang】也可以當【閃躲】用。當【閃躲】當【Bang】用時，還是必須遵守只能出一張砰的規則。
-  El Gringo - 當被任一位玩家傷害時，每扣一滴血，就可以從該玩家隨機抽一張手牌。兩滴血就抽兩張，以此類推。炸彈造成的傷害無法發動此能力。
-  Jourdonnais - 內建【酒桶】功能，當被【Bang】時，可以從遊戲牌堆抽一張牌，若是紅心則可以當作【閃躲】。若此角色裝備另一個【酒桶】，則可以有兩次抽牌機會。
-  Lucky Duke - 當發生判定需要抽牌時，他可以抽兩張，並選擇一張當要判定的牌，判定結束後抽起來的兩張都要丟棄。Ex:【酒桶】判定時，他可以抽兩張，選擇一張當作要拿來判定的牌。
-  Slab the Killer - 其他玩家要躲過他出的【Bang】必須出兩張【閃躲】。如果其他人的【酒桶】成功觸發躲過時，只算一次【閃躲】，還需要再出一張【閃躲】才能真正躲過他的【Bang】。
-  Suzy Lafayette - 沒手牌時，可以立即從遊戲牌庫頂抽一張牌。
-  Willy the Kid - 在他的回合，出【Bang】的張數沒有限制。

#### 如果死亡
  
-  殺到歹徒 - 抽3張牌
-  Vulture Sam - 當一位玩家死亡時，接收該死亡玩家的手牌和場上的【裝備牌】到自己的手牌中。

### 棄牌階段

-  檢查目前血量
-  棄牌
  
### 特殊
  
-  Sid Ketchum - 任何時刻都可以丟棄兩張卡牌，替自己補一滴血，且次數不限。


# 卡牌id

<table>
	<tr>
		<th>id</th>
		<th>數量</th>
		<th>名字</th>
		<th>中文</th>
	</tr>
	<tr>
		<td>0-24</td>
		<td>25</td>
		<td>BANG!</td>
		<td>殺</td>
	</tr>
	<tr>
		<td>25-36</td>
		<td>12</td>
		<td>MANCATO!</td>
		<td>閃</td>
	</tr>
	<tr>
		<td>37</td>
		<td>1</td>
		<td>GALTING</td>
		<td>不出閃扣一血</td>
	</tr>
	<tr>
		<td>38-39</td>
		<td>2</td>
		<td>INDIANI!</td>
		<td>不出殺扣一血</td>
	</tr>
	<tr>
		<td>40-43</td>
		<td>4</td>
		<td>PANICO!</td>
		<td>拿距離一內玩家的裝備或手牌</td>
	</tr>
	<tr>
		<td>44-47</td>
		<td>4</td>
		<td>CAT BALOU</td>
		<td>無視距離 指定玩家棄掉手牌或裝備</td>
	</tr>
	<tr>
		<td>48-49</td>
		<td>2</td>
		<td>DILIGENZA</td>
		<td>抽兩張</td>
	</tr>
	<tr>
		<td>50</td>
		<td>1</td>
		<td>WELLS FARGO</td>
		<td>抽三張</td>
	</tr>
	<tr>
		<td>51-52</td>
		<td>2</td>
		<td>EMPROIO</td>
		<td>五穀豐登</td>
	</tr>
	<tr>
		<td>53-58</td>
		<td>6</td>
		<td>BIRRA</td>
		<td>桃</td>
	</tr>
	<tr>
		<td>59</td>
		<td>1</td>
		<td>SALLON</td>
		<td>全部補一血</td>
	</tr>
	<tr>
		<td>60-62</td>
		<td>3</td>
		<td>DUELLO</td>
		<td>決鬥</td>
	</tr>
	<tr>
		<td>63-64</td>
		<td>2</td>
		<td>BARILE</td>
		<td>被殺可以判定</td>
	</tr>
	<tr>
		<td>65</td>
		<td>1</td>
		<td>MIRINO</td>
		<td>-1</td>
	</tr>
	<tr>
		<td>66-67</td>
		<td>2</td>
		<td>MUSTANG</td>
		<td>+1</td>
	</tr>
	<tr>
		<td>68-70</td>
		<td>3</td>
		<td>PRIGIONE</td>
		<td>判定 跳過回合</td>
	</tr>
	<tr>
		<td>71</td>
		<td>1</td>
		<td>DINAMITE</td>
		<td>閃電</td>
	</tr>
	<tr>
		<td>72-73</td>
		<td>2</td>
		<td>VOLCANIC</td>
		<td>連弩</td>
	</tr>
	<tr>
		<td>74-76</td>
		<td>3</td>
		<td>SCHOFIELD</td>
		<td>2</td>
	</tr>
	<tr>
		<td>77</td>
		<td>1</td>
		<td>REMINTON</td>
		<td>3</td>
	</tr>
	<tr>
		<td>78</td>
		<td>1</td>
		<td>REV.CARABINE</td>
		<td>4</td>
	</tr>
	<tr>
		<td>79</td>
		<td>1</td>
		<td>WINCHESTER</td>
		<td>5</td>
	</tr>
</table> 
