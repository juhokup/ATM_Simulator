-- MySQL dump 10.13  Distrib 8.2.0, for Win64 (x86_64)
--
-- Host: localhost    Database: atm
-- ------------------------------------------------------
-- Server version	8.2.0

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!50503 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Current Database: `atm`
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `atm` /*!40100 DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci */ /*!80016 DEFAULT ENCRYPTION='N' */;

USE `atm`;

--
-- Table structure for table `account`
--

DROP TABLE IF EXISTS `account`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `account` (
  `idaccount` int NOT NULL AUTO_INCREMENT,
  `balance` decimal(10,2) NOT NULL,
  `creditLimit` decimal(10,2) DEFAULT NULL,
  `accountNumber` char(18) NOT NULL,
  `currency_idcurrency` int NOT NULL,
  PRIMARY KEY (`idaccount`,`currency_idcurrency`),
  UNIQUE KEY `idaccount_UNIQUE` (`idaccount`),
  UNIQUE KEY `accountNumber_UNIQUE` (`accountNumber`),
  KEY `fk_account_currency1_idx` (`currency_idcurrency`),
  CONSTRAINT `fk_account_currency1` FOREIGN KEY (`currency_idcurrency`) REFERENCES `currency` (`idcurrency`)
) ENGINE=InnoDB AUTO_INCREMENT=16 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `account`
--

LOCK TABLES `account` WRITE;
/*!40000 ALTER TABLE `account` DISABLE KEYS */;
INSERT INTO `account` VALUES (4,9339.29,100.20,'123456789123456789',2),(5,6228.89,0.00,'111222333444555666',5),(6,285.00,500.00,'121232343454565676',1),(7,1850.00,1000.00,'432143214321432143',1),(8,1350.00,800.00,'987654321098765412',1),(9,2850.00,1500.00,'246801357924680189',4),(10,2500.00,1200.00,'135792468013579278',5),(11,1800.00,900.00,'802468013579246867',6),(12,2200.00,1100.00,'468013579246802456',7),(13,2700.00,1300.00,'579246802468013545',8),(14,3500.00,1800.00,'013579246802468034',2),(15,1900.00,1000.00,'924680135792468023',3);
/*!40000 ALTER TABLE `account` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card`
--

DROP TABLE IF EXISTS `card`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card` (
  `idcard` int NOT NULL AUTO_INCREMENT,
  `pin` varchar(150) NOT NULL,
  `expire` date NOT NULL,
  `type` int NOT NULL,
  `cardStatus` int NOT NULL,
  `customer_idcustomer` int NOT NULL,
  `cardNumber` char(16) NOT NULL,
  `pinAttempts` int NOT NULL,
  PRIMARY KEY (`idcard`),
  UNIQUE KEY `idcard_UNIQUE` (`idcard`),
  UNIQUE KEY `cardNumber_UNIQUE` (`cardNumber`),
  KEY `fk_card_customer1_idx` (`customer_idcustomer`),
  CONSTRAINT `fk_card_customer1` FOREIGN KEY (`customer_idcustomer`) REFERENCES `customer` (`idcustomer`)
) ENGINE=InnoDB AUTO_INCREMENT=27 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card`
--

LOCK TABLES `card` WRITE;
/*!40000 ALTER TABLE `card` DISABLE KEYS */;
INSERT INTO `card` VALUES (9,'$2a$10$Az5oL5DiGL/stTk3nwIxyeTsc6nZOouOHUCA5zPvSFZNJxJSMIcSq','2027-03-22',1,1,1,'1234567891234567',3),(15,'$2a$10$E1y0AJheUKv/3s/zACPZ0eFNMOypSBzKUaGNSZCzVq0mYXR2Obhpy','2027-04-04',3,1,1,'06000626F2',3),(25,'$2a$10$aTmhycHvt.BJtlcXt7VlLu56EVA.6nixHfhb4PRJn4APWG.fT3VBK','2027-04-08',1,1,1,'06000D8B89',3),(26,'$2a$10$io2a2Sge9dBB6WhbUcH51O83Rg6ZtBNtbCJYMyDkVpXPgK7gHh/QK','2025-03-03',1,0,1,'1234567897654321',0);
/*!40000 ALTER TABLE `card` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `card_privileges`
--

DROP TABLE IF EXISTS `card_privileges`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `card_privileges` (
  `idpriv` int NOT NULL AUTO_INCREMENT,
  `card_idcard` int NOT NULL,
  `account_idaccount` int NOT NULL,
  PRIMARY KEY (`idpriv`,`card_idcard`,`account_idaccount`),
  UNIQUE KEY `idpriv_UNIQUE` (`idpriv`),
  KEY `fk_card_has_account_account1_idx` (`account_idaccount`),
  KEY `fk_card_has_account_card1_idx` (`card_idcard`),
  CONSTRAINT `fk_card_has_account_account1` FOREIGN KEY (`account_idaccount`) REFERENCES `account` (`idaccount`),
  CONSTRAINT `fk_card_has_account_card1` FOREIGN KEY (`card_idcard`) REFERENCES `card` (`idcard`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `card_privileges`
--

LOCK TABLES `card_privileges` WRITE;
/*!40000 ALTER TABLE `card_privileges` DISABLE KEYS */;
INSERT INTO `card_privileges` VALUES (1,15,4),(2,25,6),(3,15,5);
/*!40000 ALTER TABLE `card_privileges` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Temporary view structure for view `combi_card`
--

DROP TABLE IF EXISTS `combi_card`;
/*!50001 DROP VIEW IF EXISTS `combi_card`*/;
SET @saved_cs_client     = @@character_set_client;
/*!50503 SET character_set_client = utf8mb4 */;
/*!50001 CREATE VIEW `combi_card` AS SELECT 
 1 AS `account_idaccount`,
 1 AS `card_idcard`,
 1 AS `creditLimit`*/;
SET character_set_client = @saved_cs_client;

--
-- Table structure for table `currency`
--

DROP TABLE IF EXISTS `currency`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `currency` (
  `idcurrency` int NOT NULL AUTO_INCREMENT,
  `currencyName` varchar(4) NOT NULL,
  `currencyRate` float NOT NULL,
  PRIMARY KEY (`idcurrency`),
  UNIQUE KEY `idcurrency_UNIQUE` (`idcurrency`),
  UNIQUE KEY `currency_UNIQUE` (`currencyName`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `currency`
--

LOCK TABLES `currency` WRITE;
/*!40000 ALTER TABLE `currency` DISABLE KEYS */;
INSERT INTO `currency` VALUES (1,'EUR',1),(2,'USD',1.08),(3,'JPY',164.18),(4,'GBP',0.86),(5,'SEK',11.47),(6,'NOK',11.65),(7,'ISK',149.53),(8,'VND',26826.9);
/*!40000 ALTER TABLE `currency` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `customer`
--

DROP TABLE IF EXISTS `customer`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `customer` (
  `idcustomer` int NOT NULL AUTO_INCREMENT,
  `fname` varchar(45) NOT NULL,
  `lname` varchar(45) NOT NULL,
  PRIMARY KEY (`idcustomer`),
  UNIQUE KEY `idcustomer_UNIQUE` (`idcustomer`)
) ENGINE=InnoDB AUTO_INCREMENT=9 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `customer`
--

LOCK TABLES `customer` WRITE;
/*!40000 ALTER TABLE `customer` DISABLE KEYS */;
INSERT INTO `customer` VALUES (1,'Mikko','Mallikas'),(3,'Maija','Mallikas'),(4,'Mikki','Hiiri'),(5,'Mikki','Hiiri'),(6,'Naku','Ankka'),(7,'Bad','Man'),(8,'Rob','Bing');
/*!40000 ALTER TABLE `customer` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `privileges`
--

DROP TABLE IF EXISTS `privileges`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `privileges` (
  `idprivilege` int NOT NULL AUTO_INCREMENT,
  `customer_idcustomer` int NOT NULL,
  `account_idaccount` int NOT NULL,
  PRIMARY KEY (`idprivilege`,`customer_idcustomer`,`account_idaccount`),
  UNIQUE KEY `idprivilege_UNIQUE` (`idprivilege`),
  KEY `fk_privileges_customer_idx` (`customer_idcustomer`),
  KEY `fk_privileges_account1_idx` (`account_idaccount`),
  CONSTRAINT `fk_privileges_account1` FOREIGN KEY (`account_idaccount`) REFERENCES `account` (`idaccount`),
  CONSTRAINT `fk_privileges_customer` FOREIGN KEY (`customer_idcustomer`) REFERENCES `customer` (`idcustomer`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `privileges`
--

LOCK TABLES `privileges` WRITE;
/*!40000 ALTER TABLE `privileges` DISABLE KEYS */;
/*!40000 ALTER TABLE `privileges` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `transaction`
--

DROP TABLE IF EXISTS `transaction`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!50503 SET character_set_client = utf8mb4 */;
CREATE TABLE `transaction` (
  `idtransaction` int NOT NULL AUTO_INCREMENT,
  `balanceChange` decimal(10,2) NOT NULL,
  `type` tinyint NOT NULL,
  `date` datetime NOT NULL,
  `location` varchar(72) NOT NULL,
  `account_idaccount` int NOT NULL,
  PRIMARY KEY (`idtransaction`),
  UNIQUE KEY `idtransaction_UNIQUE` (`idtransaction`),
  KEY `fk_transaction_account1_idx` (`account_idaccount`),
  CONSTRAINT `fk_transaction_account1` FOREIGN KEY (`account_idaccount`) REFERENCES `account` (`idaccount`)
) ENGINE=InnoDB AUTO_INCREMENT=53 DEFAULT CHARSET=utf8mb3;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `transaction`
--

LOCK TABLES `transaction` WRITE;
/*!40000 ALTER TABLE `transaction` DISABLE KEYS */;
INSERT INTO `transaction` VALUES (1,10.00,1,'2024-04-10 09:54:35','Oulu',4),(2,10.00,1,'2024-04-10 09:59:46','Oulu',4),(3,150.00,1,'2024-04-10 10:03:15','Oulu',5),(4,150.00,1,'2024-04-10 10:03:18','Oulu',6),(5,150.00,1,'2024-04-10 10:03:21','Oulu',7),(6,150.00,1,'2024-04-10 10:03:23','Oulu',8),(7,150.00,1,'2024-04-10 10:03:25','Oulu',9),(8,5.00,1,'2024-04-10 10:58:25','Oulu',5),(9,5.00,1,'2024-04-10 10:58:31','Oulu',4),(10,5.00,1,'2024-04-12 10:34:58','Oulu',5),(11,60.00,1,'2024-04-12 10:35:49','Oulu',5),(12,5.00,1,'2024-04-16 14:29:04','Oulu',5),(13,5.00,1,'2024-04-16 14:30:30','Oulu',5),(14,10.00,1,'2024-04-16 14:31:29','Oulu',5),(15,10.00,1,'2024-04-16 14:32:08','Oulu',5),(16,60.00,1,'2024-04-16 14:38:04','Oulu',5),(17,10.00,1,'2024-04-16 14:40:27','Oulu',5),(18,10.00,1,'2024-04-16 14:42:42','Oulu',5),(19,10.00,1,'2024-04-16 14:44:21','Oulu',5),(20,5.00,1,'2024-04-16 14:46:08','Oulu',5),(21,5.00,1,'2024-04-16 14:55:36','Oulu',5),(22,5.00,1,'2024-04-16 14:55:49','Oulu',5),(23,-20.00,1,'2024-04-19 11:39:14','Oulu',5),(24,-1.22,1,'2024-04-19 11:39:42','Oulu',5),(25,-20.00,1,'2024-04-19 11:40:48','Oulu',4),(26,-17.44,1,'2024-04-19 11:41:09','Oulu',4),(27,-20.00,1,'2024-04-19 15:37:59','Oulu',4),(28,-200.00,1,'2024-04-19 15:50:03','Oulu',4),(29,-20.00,1,'2024-04-19 15:50:54','Oulu',4),(30,-50.00,1,'2024-04-19 15:51:43','Oulu',4),(31,-18.27,1,'2024-04-20 20:57:26','Oulu',4),(32,-20.00,1,'2024-04-22 11:44:43','Oulu',4),(33,-20.00,1,'2024-04-22 11:48:12','Oulu',5),(34,-20.00,1,'2024-04-22 12:41:35','Oulu',6),(35,-200.00,1,'2024-04-22 13:12:49','Oulu',5),(36,-20.00,1,'2024-04-22 13:15:19','Oulu',4),(37,-40.00,1,'2024-04-22 13:15:43','Oulu',4),(38,-200.00,1,'2024-04-22 13:16:07','Oulu',4),(39,-35.00,1,'2024-04-22 13:16:29','Oulu',4),(40,-1100.00,1,'2024-04-23 10:32:18','Oulu',5),(41,-1279.07,1,'2024-04-23 10:32:49','Oulu',5),(42,-60.91,1,'2024-04-23 10:33:17','Oulu',5),(43,-999.00,1,'2024-04-23 12:32:48','Oulu',5),(44,-90.91,1,'2024-04-23 12:33:34','Oulu',5),(45,-20.00,1,'2024-04-24 16:30:11','Oulu',6),(46,-15.00,1,'2024-04-24 16:41:57','Oulu',6),(47,-250.00,1,'2024-04-24 16:42:32','Oulu',6),(48,-50.00,1,'2024-04-24 16:42:35','Oulu',6),(49,-30.00,1,'2024-04-24 16:42:37','Oulu',6),(50,-100.00,1,'2024-04-24 16:42:41','Oulu',6),(51,-40.00,1,'2024-04-24 16:42:47','Oulu',6),(52,-40.00,1,'2024-04-24 16:43:51','Oulu',6);
/*!40000 ALTER TABLE `transaction` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Current Database: `atm`
--

USE `atm`;

--
-- Final view structure for view `combi_card`
--

/*!50001 DROP VIEW IF EXISTS `combi_card`*/;
/*!50001 SET @saved_cs_client          = @@character_set_client */;
/*!50001 SET @saved_cs_results         = @@character_set_results */;
/*!50001 SET @saved_col_connection     = @@collation_connection */;
/*!50001 SET character_set_client      = utf8mb4 */;
/*!50001 SET character_set_results     = utf8mb4 */;
/*!50001 SET collation_connection      = utf8mb4_0900_ai_ci */;
/*!50001 CREATE ALGORITHM=UNDEFINED */
/*!50013 DEFINER=`root`@`localhost` SQL SECURITY DEFINER */
/*!50001 VIEW `combi_card` AS select `card_privileges`.`account_idaccount` AS `account_idaccount`,`card_privileges`.`card_idcard` AS `card_idcard`,`account`.`creditLimit` AS `creditLimit` from (`card_privileges` join `account`) where (`card_privileges`.`account_idaccount` = `account`.`idaccount`) */;
/*!50001 SET character_set_client      = @saved_cs_client */;
/*!50001 SET character_set_results     = @saved_cs_results */;
/*!50001 SET collation_connection      = @saved_col_connection */;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2024-04-24 13:44:06
