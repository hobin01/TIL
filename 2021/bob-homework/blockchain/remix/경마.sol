// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.7.0 <0.9.0;

contract Racing {
        
    uint256 batting; // batting money
    uint256 reward; // reward money 
    uint[3] ranking; // slot numbers
    uint horse; // choose horse number 1~3
    uint[3][6] combination; // using for random ranking 
    uint winner = 0;
    
    /* batting money */
    function put_money(uint256 money) public {
        batting = money;
    }
    
    /* information */
    function Info() public pure returns(string memory info){
        info = "you can choose 1 ~ 3. if you choose winner, then you'll take double.";
        return info;
    }
    
    /* choose horse and make combination */
    function choose_horse(uint num) public {
        require(num > 0 && num < 3); // horse num : 1 ~ 3
        horse = num;
        
        combination[0] = [1,2,3];
        combination[1] = [1,3,2];
        combination[2] = [2,1,3];
        combination[3] = [2,3,1];
        combination[4] = [3,1,2];
        combination[5] = [3,2,1];
    }
    
    /* racing start */
    function racing() public returns(string memory message){
        
        /* batting money : not negative */
        require(batting > 0);    
        
        uint randNum = uint(uint256(keccak256(abi.encodePacked(block.timestamp, block.difficulty))) % 6);
        ranking[0] = combination[randNum][0];
        ranking[1] = combination[randNum][1];
        ranking[2] = combination[randNum][2];
        
        if(ranking[0] == 1)
            winner = 1;
        else if(ranking[1] == 1)
            winner = 2;
        else if(ranking[2] == 1)
            winner = 3;
        
        if(horse == winner){
            message = "you win";
            reward = batting * 2;
        }
        else{
            message = "you lose";
            reward = 0;
        }
        
        return message;
    }
    
    /* show reward */
    function show_reward() public view returns(uint256 money){
        money = reward;
        return money;
    }
    
    /* show winner */
    function show_winner() public view returns(uint){
        require(winner > 0);
        return winner;
    }
    
}