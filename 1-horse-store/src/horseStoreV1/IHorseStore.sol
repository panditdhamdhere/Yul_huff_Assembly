// SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.25;

interface IHorseStore {
    function updateHorseNumber(uint256 newNumberOfHorses) external;

    function readNumberOfHorses() external view returns (uint256);
}
