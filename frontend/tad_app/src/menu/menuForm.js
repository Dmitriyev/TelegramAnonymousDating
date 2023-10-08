import React from 'react';
import './menuForm.css';
import { Link } from 'react-router-dom';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';

function Menu() {

  return (
    <div className="index-menu">
    <div className="div-menu">
      <div className="overlap-menu">
        <img
          className="polygon-menu"
          alt="Polygon"
          src="https://cdn.animaapp.com/projects/6522593a895771eda12b6b7a/releases/652259ebd148241fab287b78/img/polygon-1.svg"
        />
        <div className="text-wrapper-menu">ПРОФИЛЬ</div>
      </div>
      <div className="overlap-group-menu">
        <div className="rectangle-menu" />
        <div className="rectangle-menu-2" />
        <img
          className="element-menu"
          alt="Element"
          src="https://cdn.animaapp.com/projects/6522593a895771eda12b6b7a/releases/652259ebd148241fab287b78/img/-------2-1-1@2x.png"
        />
        <div className="ellipse-menu" />
        <img
          className="img-menu"
          alt="Element"
          src="https://cdn.animaapp.com/projects/6522593a895771eda12b6b7a/releases/652259ebd148241fab287b78/img/-----1.png"
        />
        <div className="rectangle-menu-3" />
        <div className="rectangle-menu-4" />
        <div className="text-wrapper-menu-2">+</div>
        <div className="rectangle-menu-5" />
        <div className="text-wrapper-menu-3">ИРИНА, 25</div>
        <div className="rectangle-menu-6" />
        <div className="text-wrapper-menu-4">
          <Link to="/search">
            ПОИСК ПАРЫ
            </Link>
            </div>
        <div className="rectangle-menu-7" />
        <div className="text-wrapper-menu-5">КТО ПОСТАВИЛ ЛАЙК</div>
        <div className="rectangle-menu-8" />
        <div className="text-wrapper-menu-6">
          <Link to="/registration">
          РЕДАКТИРОВАТЬ ПРОФИЛЬ
          </Link>
          </div>
        <div className="rectangle-menu-9" />
        <div className="text-wrapper-menu-7">ЧАТЫ</div>
        <img
          className="element-menu-2"
          alt="Element"
          src="https://cdn.animaapp.com/projects/6522593a895771eda12b6b7a/releases/652259ebd148241fab287b78/img/-------1-1.png"
        />
        <img
          className="element-menu-3"
          alt="Element"
          src="https://cdn.animaapp.com/projects/6522593a895771eda12b6b7a/releases/652259ebd148241fab287b78/img/-----1-1.png"
        />
        <img
          className="element-menu-4"
          alt="Element"
          src="https://cdn.animaapp.com/projects/6522593a895771eda12b6b7a/releases/652259ebd148241fab287b78/img/----------------------1.png"
        />
        <img
          className="element-menu-5"
          alt="Element"
          src="https://cdn.animaapp.com/projects/6522593a895771eda12b6b7a/releases/652259ebd148241fab287b78/img/-----1-2.png"
        />
      </div>
    </div>
  </div>
);
};
export default Menu;
