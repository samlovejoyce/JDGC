/* This file was generated by ODB, object-relational mapping (ORM)
 * compiler for C++.
 */

DROP TABLE IF EXISTS `real_terrain`;

CREATE TABLE `real_terrain` (
  `xblocksno` INT NOT NULL,
  `yblocksno` INT NOT NULL,
  `xblocksize` INT NOT NULL,
  `yblocksize` INT NOT NULL,
  `zdata` MEDIUMBLOB NOT NULL)
 ENGINE=InnoDB;

CREATE INDEX `xIdx` USING BTREE
  ON `real_terrain` (`xblocksno` DESC);

CREATE INDEX `yIdx` USING BTREE
  ON `real_terrain` (`yblocksno` DESC);

