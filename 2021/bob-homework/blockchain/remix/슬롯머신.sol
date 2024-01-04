// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.7.0 <0.9.0;

contract SlotMachine {
    
    uint256 reward; // reward money 
    uint16[3] numbers; // slot numbers
    
    function Info() public pure returns(string memory info){
        info = "if you get the three same numbers, then you'll take 100 times.";
        return info;
    }
    
    function game(uint256 batting) public returns(string memory message){
           
        require(batting > 0); // No negative batting manoey
        
        /* random numbers for game */
        uint16 randNum1 = uint16(uint256(keccak256(abi.encodePacked(block.timestamp + 123, block.difficulty))) % 10);
        uint16 randNum2 = uint16(uint256(keccak256(abi.encodePacked(block.timestamp + 456, block.difficulty))) % 10);
        uint16 randNum3 = uint16(uint256(keccak256(abi.encodePacked(block.timestamp + 789, block.difficulty))) % 10);
        
        numbers[0] = randNum1;
        numbers[1] = randNum2;
        numbers[2] = randNum3;
        
        if(numbers[0] == numbers[1] && numbers[1] == numbers[2]){
            
            reward = batting * 100;
            message = "you win!!";
        }
        
        else{
            reward = 0;
            message = "you lose";
        }
        
        return message;
    }
    
    function show_numbers() public view returns(uint32 got_number){
        got_number = 0;
        got_number += (numbers[0] * 100);
        got_number += (numbers[1] * 10);
        got_number += (numbers[2]);
        
        return got_number;
    }
    
    function show_reward() public view returns(uint256 money){
        money = reward;
        return money;
    }
}