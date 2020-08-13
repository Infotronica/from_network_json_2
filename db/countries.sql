-- phpMyAdmin SQL Dump
-- version 4.9.5
-- https://www.phpmyadmin.net/
--
-- Servidor: localhost:3306
-- Tiempo de generación: 13-08-2020 a las 04:09:43
-- Versión del servidor: 5.7.31-cll-lve
-- Versión de PHP: 7.3.6

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `countries`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `countries list`
--

DROP TABLE IF EXISTS `countries list`;
CREATE TABLE `countries list` (
  `icountry` int(10) UNSIGNED NOT NULL,
  `country` varchar(100) DEFAULT NULL,
  `capital` varchar(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Volcado de datos para la tabla `countries list`
--

INSERT INTO `countries list` (`icountry`, `country`, `capital`) VALUES
(1, 'AFGHANISTAN', NULL),
(2, 'ALBANIA', NULL),
(3, 'ALGERIA', NULL),
(4, 'ANDORRA', NULL),
(5, 'ANGOLA', NULL),
(6, 'ANTIGUA AND BARBUDA', NULL),
(7, 'ARGENTINA', NULL),
(8, 'ARMENIA', NULL),
(9, 'AUSTRALIA', NULL),
(11, 'INDIA', NULL),
(12, 'MEXICO', NULL),
(13, 'SPAIN', NULL);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `countries list`
--
ALTER TABLE `countries list`
  ADD PRIMARY KEY (`icountry`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `countries list`
--
ALTER TABLE `countries list`
  MODIFY `icountry` int(10) UNSIGNED NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=14;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
