// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.7.0 <0.9.0;

contract Baseball {

    mapping(uint => string) table;
    
    /* strike and ball */
    function make_table() public {
        table[0] = "0 strike 0 ball";
        table[1] = "0 strike 1 ball";
        table[2] = "0 strike 2 ball";
        table[3] = "0 strike 3 ball";
        table[10] = "1 strike 0 ball";
        table[11] = "1 strike 1 ball";
        table[12] = "1 strike 2 ball";
        table[20] = "2 strike 0 ball";
        table[21] = "2 strike 1 ball";
        table[30] = "3 strike 0 ball";
    }
    
    /* information for game */
    /* information */
    function Info() public pure returns(string memory info){
        info = "Baseball Game!";
        return info;
    }
    
    /* make computer's random number */
    uint num1;
    uint num2;
    uint num3;
    function make_numbers() public{
        while(true){
            num1 = uint(uint256(keccak256(abi.encodePacked(block.timestamp + 123, block.difficulty))) % 9) + 1;
            num2 = uint(uint256(keccak256(abi.encodePacked(block.timestamp + 456, block.difficulty))) % 9) + 1;
            num3 = uint(uint256(keccak256(abi.encodePacked(block.timestamp + 789, block.difficulty))) % 9) + 1;
            
            if(num1 != num2 && num2 != num3 && num1 != num3)
                break;
        }
    }
    
    /* baseball game */
    function game(uint num) public view returns(string memory message){
        
        uint x;
        uint y;
        uint z;
        
        x = num / 100;
        y = (num /10) % 10;
        z = num % 10;
        
        /* no same number and no zeors */
        require(x !=0 && y !=0 && z != 0 && x != y && y != z && z != x);
        
        /* check strikes and balls. result : 10 * #strike + #ball*/
        uint strike = 0;
        uint ball = 0;
        uint result = 0;
        
        if(x == num1)
            strike += 1;
        if(y == num2)
            strike += 1;
        if(z == num3)
            strike += 1;
            
        if(x == num2 || x == num3)
            ball += 1;
        if(y == num1 || y == num3)
            ball += 1;
        if(z == num1 || z == num2)
            ball += 1;
        
        result = 10 * strike + ball;
        
        message = table[result];
        
        return message;
    }
    
}