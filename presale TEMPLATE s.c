// SPDX-License-Identifier: MIT
pragma solidity ^0.8.9;

import "@openzeppelin/contracts@4.8.3/token/ERC20/IERC20.sol";

contract Presale {
    IERC20 public token;
    address payable public wallet;
    uint256 public rate;

    constructor(IERC20 _token, address payable _wallet, uint256 _rate) {
        token = _token;
        wallet = _wallet;
        rate = _rate;
    }

    function buyTokens() public payable {
        require(msg.value > 0, "You need to send some ether");
        uint256 tokens = msg.value * rate;
        require(token.balanceOf(address(this)) >= tokens, "Not enough tokens left in the presale");

        wallet.transfer(msg.value); // forward the funds to the wallet
        token.transfer(msg.sender, tokens); // send tokens to the participant
    }
}
