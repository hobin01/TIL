// SPDX-License-Identifier: GPL-3.0

pragma solidity >=0.7.0 <0.9.0;

contract RSP_game {
    
    uint8 com; 
    /* computer random number - 0 : rock, 1 : scissors, 2 : paper */
    uint8 myNum;
    
    /* random number of computer */
    function random_com() public {
        com = uint8(uint256(keccak256(abi.encodePacked(block.timestamp, block.difficulty))) % 3);
    }
    
    /* put my number - 0 : rock, 1 : scissors, 2 : paper */
    function put_my_num(uint8 num) public {
        myNum = num;
    }
    
    /* show com number */
    function show_com_num() public view returns (uint8){
        return com;
    }
    
    /* information */
    function Info() public pure returns (string memory info){
        info = "0 : rock, 1 : scissors, 2 : paper";
        return info;
    }
    
    /* rock scissors paper game*/
    function RSP() public view returns (string memory result) {
        
        if(com == 1){
            if(myNum == 1){
                result = "draw";
            }
            else if(myNum == 2){
                result = "lose";
            }
            else if(myNum == 0){
                result = "win";
            }
        }
        else if(com == 2){
            if(myNum == 1){
                result = "win";
            }
            else if(myNum == 2){
                result = "draw";
            }
            else if(myNum == 0){
                result = "lose";
            }
        }
        else if(com == 0){
            if(myNum == 1){
                result = "lose";
            }
            else if(myNum == 2){
                result = "win";
            }
            else if(myNum == 0){
                result = "draw";
            }
        }
        
        return result;
    }
}