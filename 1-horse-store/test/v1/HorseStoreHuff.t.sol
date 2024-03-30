// SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.25;
import {Base_TestV1, HorseStore} from "./Base_TestV1.t.sol";

import {HuffDeployer} from "foundry-huff/HuffDeployer.sol";

contract HorseStoreHuff is Base_TestV1 {
    string public constant HORSE_STORE_HUFF_LOCATION =
        "horseStoreV1/HorseStore";

    function setUp() public override {
        // horseStore = huff edition
        horseStore = HorseStore(
            HuffDeployer.config().deploy(HORSE_STORE_HUFF_LOCATION)
        );
    }
}
