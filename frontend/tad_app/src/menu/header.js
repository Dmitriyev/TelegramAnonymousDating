import React, { useState, useEffect } from 'react';
import './registrationForm.js'
function Header() {
    const [telegramId, setTelegramId] = useState('');

    const extractTelegramData = () => {
        const initData = window.TelegramWebApp?.initData;
      
        if (initData) {
          const telegramId = initData.telegramId;
          setTelegramId(telegramId);
        }
      };
    // return(
    //     // <nav class="bg-dark navbar-dark navbar">
    //     //     <div className="row col-12 d-flex justify-content-center text-white">
    //     //         <h3>Registration</h3>
    //     //     </div>
    //     // </nav>
    // )
}
export default Header;
