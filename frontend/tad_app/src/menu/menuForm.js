import React from 'react';
// import './style.css';
import { Link } from 'react-router-dom';
function Menu() {

    return (
      <div>
        <Link to="/search">Search for a couple</Link>
        <Link to="/liked">Those who liked me</Link>
        <Link to="/edit-profile">Edit profile</Link>
        <Link to="/chats">Chats</Link>
      </div>
    );
  }
  
  export default Menu;
  