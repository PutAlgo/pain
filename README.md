# pain
xyzzy






// SPDX-License-Identifier: MIT
pragma solidity ^0.8.9;

import "@openzeppelin/contracts@4.8.3/token/ERC20/ERC20.sol";
import "@openzeppelin/contracts@4.8.3/token/ERC20/extensions/ERC20Burnable.sol";
import "@openzeppelin/contracts@4.8.3/token/ERC20/extensions/ERC20Snapshot.sol";
import "@openzeppelin/contracts@4.8.3/access/Ownable.sol";
import "@openzeppelin/contracts@4.8.3/token/ERC20/extensions/draft-ERC20Permit.sol";
import "@openzeppelin/contracts@4.8.3/token/ERC20/extensions/ERC20Votes.sol";

contract PAINCoin is ERC20, ERC20Burnable, ERC20Snapshot, Ownable, ERC20Permit, ERC20Votes {
    address public foundationReserve;
    address public treasury;
    address public teamAndMarketing;

    constructor(address _foundationReserve, address _treasury, address _teamAndMarketing) ERC20("PAINCoin", "PAIN") ERC20Permit("PAINCoin") {
        foundationReserve = _foundationReserve;
        treasury = _treasury;
        teamAndMarketing = _teamAndMarketing;

        uint256 totalSupply = 1000000000 * 10 ** decimals();

        _mint(foundationReserve, totalSupply * 10 / 100);
        _mint(treasury, totalSupply * 10 / 100);
        _mint(teamAndMarketing, totalSupply * 5 / 100);
        _mint(msg.sender, totalSupply * 75 / 100);
    }

    function snapshot() public onlyOwner {
        _snapshot();
    }

    function mint(address to, uint256 amount) public onlyOwner {
        _mint(to, amount);
    }

    function _transfer(address sender, address recipient, uint256 amount) internal virtual override {
        super._transfer(sender, recipient, amount);

        if (sender != treasury && recipient != treasury) {
            uint256 burnAmount = amount / 10000; // 0.01%
            _burn(treasury, burnAmount);
        }
    }

    // The following functions are overrides required by Solidity.

    function _beforeTokenTransfer(address from, address to, uint256 amount)
        internal
        override(ERC20, ERC20Snapshot)
    {
        super._beforeTokenTransfer(from, to, amount);
    }

    function _afterTokenTransfer(address from, address to, uint256 amount)
        internal
        override(ERC20, ERC20Votes)
    {
        super._afterTokenTransfer(from, to, amount);
    }

    function _mint(address to, uint256 amount)
        internal
        override(ERC20, ERC20Votes)
    {
        super._mint(to, amount);
    }

    function _burn(address account, uint256 amount)
        internal
        override(ERC20, ERC20Votes)
    {
        super._burn(account, amount);
    }
}
