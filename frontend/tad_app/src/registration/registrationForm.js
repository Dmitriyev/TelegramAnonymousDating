import React, { useState, useEffect } from 'react';
import './style.css';
import { authToken } from './header.js';


function RegistrationPage() {
  const [name, setName] = useState('');
  const [age, setAge] = useState('');
  const [gender, setGender] = useState('');
  const [orientation, setOrientation] = useState('');
  const [city, setCity] = useState('');
  const [bio, setBio] = useState('');
  const [error, setError] = useState('');
  const [selectedFile, setSelectedFile] = useState(null);

  const [telegramId, setTelegramId] = useState('');
  const [photoUrl, setPhotoUrl] = useState('');

  useEffect(() => {
    if (window.Telegram && window.Telegram.WebApp && window.Telegram.WebApp.initDataUnsafe) {
      const initDataUnsafeContent = JSON.stringify(window.Telegram.WebApp.initDataUnsafe);

      const initDataUnsafeField = document.getElementById('initDataUnsafe');

      if (initDataUnsafeField) {
        initDataUnsafeField.value = initDataUnsafeContent;
      }
    }
  }, []);

  useEffect(() => {
    if (window.Telegram && window.Telegram.WebApp && window.Telegram.WebApp.initData) {
      const initDataContent = JSON.stringify(window.Telegram.WebApp.initData);

      const initDataField = document.getElementById('initData');
      
      if (initDataField) {
        initDataField.value = initDataContent;
      }
    }
  }, []);


  const [isDarkTheme, setIsDarkTheme] = useState(false); // Check dark theme

  useEffect(() => {
    // Check dark theme is active
    if (
      window.matchMedia &&
      window.matchMedia('(prefers-color-scheme: dark)').matches
    ) {
      setIsDarkTheme(true);
    }
  }, []);

  const validateName = (inputName) => {
    const trimmedName = inputName.trim();
    const nameRegex = /^[A-Za-z\s]+$/;
    if (!nameRegex.test(trimmedName)) {
        setError('Name should contain only letters and spaces.');
        return false;
      }
      
      if (trimmedName.length > 20) {
        setError('Name should not exceed 20 characters.');
        return false;
      }
    setError('');
    setName(trimmedName);
    return true;
    };

  const validateAge = (inputAge) => {
    if (/^\d+$/.test(inputAge) && inputAge.length <= 2) {
      setError('');
      return true;
    } else {
      setError('Age must consist of numbers only and no more than 2 characters');
      return false;
    }
  };
  
  const handleFileChange = (e) => {
    const file = e.target.files[0];
    setSelectedFile(file);
  };

//   const handleSubmit = (e) => {
//     e.preventDefault();
//     if (!selectedFile) {
//       setError('Please upload your photo');
//       return;
//     }
//     if (validateName(name) && validateAge(age) && !error) {
//       console.log('Data sent to server:', name, age, gender, orientation, city, bio);
//       if (selectedFile) {
//         console.log('Upload photo:', selectedFile);
//       }
//     }
//   };

const uploadPhotoAndGetUrl = () => {
    const formData = new FormData();
    formData.append('photo', selectedFile);

    fetch('uploadphoto/api/228', {
      method: 'POST',
      body: formData,
    })
      .then((response) => response.json())
      .then((data) => {
        if (data && data.photoUrl) {
          setPhotoUrl(data.photoUrl);
        }
      })
      .catch((error) => {
        console.error('error upload:', error);
      });
  };

  const handleSubmit = (e) => {
    e.preventDefault();
    if (validateName(name) && validateAge(age) && !error) {
      if (photoUrl) {
        const userData = {
          name: name,
          age: age,
          gender: gender,
          orientation: orientation,
          city: city,
          bio: bio,
          telegramId: telegramId, 
          photoUrl: photoUrl, 
        };

        fetch('register/api/228', {
          method: 'POST',
          headers: {
            'Content-Type': 'application/json',
          },
          body: JSON.stringify(userData),
        })
          .then((response) => {
            if (response.status === 200) {
              console.log('200');
            } else {
              console.error('400');
            }
          })
          .catch((error) => {
            console.error('error:', error);
          });
      } else {
        setError('500');
      }
    }
  };

  return (
    <div className={`registration-page ${isDarkTheme ? 'dark-theme' : ''}`}>
      {/* <div className="back-button">
        <button>Back</button>
      </div> */}
      <h1>Welcome</h1>
      <label htmlFor="file" className="upload-button">
        Choose Your Photo
        <input
          type="file"
          id="file"
          accept="image/*"
          style={{ display: 'none' }}
          onChange={handleFileChange}
        />
      </label>
      <div className="image-preview">
        {selectedFile ? (
          <img src={URL.createObjectURL(selectedFile)} alt="Profile" />
        ) : (
          <div className="placeholder">Preview</div>
        )}
      </div>
      <form onSubmit={handleSubmit}>
        <div className="form-group">
          <label htmlFor="Name">Name</label>
          <input
            type="text"
            id="Name"
            value={name}
            onChange={(e) => setName(e.target.value)}
          />
        </div>
        <div className="form-group">
          <label htmlFor="Age">Age</label>
          <input
            type="number"
            id="Age"
            value={age}
            onChange={(e) => setAge(e.target.value)}
          />
        </div>
        <script src="https://telegram.org/js/telegram-web-app.js"></script>
        <div className="form-group">
          <label htmlFor="Gender">Gender</label>
          <select id="Gender" value={gender} onChange={(e) => setGender(e.target.value)}>
            <option value="Male">Male</option>
            <option value="Female">Female</option>
            {/* <option value="Other">Other</option>
            <option value="Prefer not to say">Prefer not to say</option>
            <option value="Non-binary">Non-binary</option> */}
          </select>
        </div>
        <div className="form-group">
          <label htmlFor="Orientation">Orientation</label>
          <select
            id="Orientation"
            value={orientation}
            onChange={(e) => setOrientation(e.target.value)}
          >
            <option value="Straight">Straight</option>
            <option value="Gay">Gay</option>
            {/* <option value="Lesbian">Lesbian</option> */}
            <option value="Bisexual">Bisexual</option>
            {/* <option value="Other">Other</option> */}
          </select>
        </div>
        <div className="form-group">
          <label htmlFor="City">City</label>
          <select id="City" value={city} onChange={(e) => setCity(e.target.value)}>
            <option value="New York">New York</option>
            <option value="Los Angeles">Moscow</option>
            <option value="Chicago">Rome</option>
            {/* <option value="San Francisco">San Francisco</option>
            <option value="Miami">Miami</option> */}
          </select>
        </div>
        <div className="form-group">
          <label htmlFor="Bio">Bio</label>
          <textarea
            id="Bio"
            placeholder='Enter your Bio'
            value={bio}
            onChange={(e) => setBio(e.target.value)}
          />
        </div>
        <div className="form-group">
            <input id="initData" type="text" />
        </div>
        <div className="form-group">
            <input id="initDataUnsafe" type="text" />
         </div>
        {error && <p className="error">{error}</p>}
        <div className="form-group center">
          <button type="submit" className="start-search-button">
            Start Search
          </button>
        </div>
      </form>
    </div>
  );
}

export default RegistrationPage;
