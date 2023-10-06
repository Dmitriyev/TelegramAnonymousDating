import React from 'react';
import './menuForm.css';
import { Link } from 'react-router-dom';
import { BrowserRouter as Router, Route, Switch } from 'react-router-dom';

function Menu() {

  return (
       <div className="overlap-group-wrapper">
      <div className="div-1">
        <div className="overlap">
          <img
            className="polygon"
            alt="Polygon"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/polygon-1-2@2x.png"
          />
          <p className="span-wrapper">
            <span className="text-wrapper">Profile</span>
          </p>
        </div>
        <div className="overlap-group">
          <div className="rectangle" />
          <div className="rectangle-2" />
          <img
            className="element"
            alt="Element"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/-------2-1-2@2x.png"
          />
          <div className="ellipse" />
          <img
            className="img"
            alt="Element"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/-----1-1@2x.png"
          />
          <div className="rectangle-3" />
          <div className="rectangle-4" />
          <p className="p">
            <span className="span">+</span>
          </p>
          <div className="rectangle-5" />
          <p className="element-2">
            <span className="text-wrapper-2">Name, Age</span>
          </p>
          <div className="rectangle-6" />
          <p className="span-wrapper-2">
            <span className="text-wrapper-3">Search</span>
          </p>
          <div className="rectangle-7" />
          <p className="span-wrapper-3">
            <span className="text-wrapper-3">Those who like me</span>
          </p>
          <div className="rectangle-8" />
          <p className="span-wrapper-4">
            <span className="text-wrapper-3">
            <Link to="/">
              Edit Profile
              </Link>
              </span>
          </p>
          <div className="rectangle-9" />
          <p className="span-wrapper-5">
            <span className="text-wrapper-3">Search Settig</span>
          </p>
          <img
            className="element-3"
            alt="Element"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/-------1-2@2x.png"
          />
          <img
            className="element-4"
            alt="Element"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/-----1-2@2x.png"
          />
          <img
            className="element-5"
            alt="Element"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/----------------------1-1@2x.png"
          />
          <img
            className="element-6"
            alt="Element"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/-----1-3@2x.png"
          />
        </div>
      </div>
    </div>
  );
};
export default Menu;
