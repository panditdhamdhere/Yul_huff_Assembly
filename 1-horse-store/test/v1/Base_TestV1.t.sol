// SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.25;

import {Test, console2} from "forge-std/Test.sol";
import {HorseStore} from "../../src/horseStoreV1/HorseStore.sol";
import {IHorseStore} from "../../src/horseStoreV1/IHorseStore.sol";
// import {HorseStoreYul} from "../../src/horseStoreV1/HorseStoreYul.sol";

abstract contract Base_TestV1 is Test {
    IHorseStore public horseStore;

    bytes yulCode = 
        "\x19\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00";

    function setUp() public virtual {
        horseStore = IHorseStore(address(new HorseStore()));
    }

    function testReadValue() public {
        uint256 initialValue = horseStore.readNumberOfHorses();
        assertEq(initialValue, 0);
    }

    function testWriteValue(uint256 numberOfHorses) public {
        horseStore.updateHorseNumber(numberOfHorses);
        assertEq(horseStore.readNumberOfHorses(), numberOfHorses);
    }
}
