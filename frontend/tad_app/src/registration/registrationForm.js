import React, { useState, useEffect } from "react";
import "./style.css";
import { Link } from "react-router-dom";
import {
  BrowserRouter as Router,
  Route,
  Switch,
  useNavigate,
} from "react-router-dom";
import md5 from "md5";
function RegistrationPage() {
  const [name, setName] = useState("");
  const [age, setAge] = useState("");
  const [gender, setGender] = useState("");
  const [orientation, setOrientation] = useState("");
  const [city, setCity] = useState("");
  const [bio, setBio] = useState("");
  const [error, setError] = useState("");
  const [selectedFile, setSelectedFile] = useState(undefined);
  const [telegramId, setTelegramId] = useState("121444562");
  const [photoUrl, setPhotoUrl] = useState("");
  const [isUserRegistered, setIsUserRegistered] = useState(false);
  const navigate = useNavigate();
  const id = telegramId;

  useEffect(() => {
    fetch(`https://testing.teanda.ru/api/start?user_id=${id}`)
      .then((response) => response.json())
      .then((data) => {
        setIsUserRegistered(data.isRegistered);
      })
      .catch((error) => {
        console.error("Server error", error);
      });
  }, []);

  useEffect(() => {
    if (
      window.Telegram &&
      window.Telegram.WebApp &&
      window.Telegram.WebApp.initDataUnsafe
    ) {
      const initDataUnsafeContent = JSON.stringify(
        window.Telegram.WebApp.initDataUnsafe
      );
      const initDataUnsafeField = document.getElementById("initDataUnsafe");
      if (initDataUnsafeField) {
        initDataUnsafeField.value = initDataUnsafeContent;
      }
    }
  }, []);

  useEffect(() => {
    if (
      window.Telegram &&
      window.Telegram.WebApp &&
      window.Telegram.WebApp.initData
    ) {
      const initDataContent = JSON.stringify(window.Telegram.WebApp.initData);
      const initDataField = document.getElementById("initData");
      if (initDataField) {
        initDataField.value = initDataContent;
      }
    }
  }, []);

  // const [isDarkTheme, setIsDarkTheme] = useState(false); // Check dark theme

  // useEffect(() => {
  //   // Check dark theme is active
  //   if (
  //     window.matchMedia &&
  //     window.matchMedia("(prefers-color-scheme: dark)").matches
  //   ) {
  //     setIsDarkTheme(true);
  //   }
  // }, []);

  const validateName = (inputName) => {
    const trimmedName = inputName.trim();
    const nameRegex = /^[A-Za-z\s]+$/;
    if (!nameRegex.test(trimmedName)) {
      setError("Name should contain only letters and spaces.");
      return false;
    }
    if (trimmedName.length > 20) {
      setError("Name should not exceed 20 characters.");
      return false;
    }
    setError("");
    setName(trimmedName);
    return true;
  };

  const validateAge = (inputAge) => {
    if (/^\d+$/.test(inputAge) && inputAge.length <= 2) {
      setError("");
      return true;
    } else {
      setError(
        "Age must consist of numbers only and no more than 2 characters"
      );
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
    formData.append("photo", selectedFile);
    return fetch(
      `https://testing.teanda.ru/mds/upload?tg_id=${id}&format=jpg`,
      {
        method: "POST",
        body: formData,
      }
    )
      .then((response) => response.json())
      .then((data) => {
        if (data && data.photoUrl) {
          setPhotoUrl(data.photoUrl);
        }
      })
      .catch((error) => {
        console.error("error upload:", error);
      });
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (validateName(name) && validateAge(age) && !error) {
      await uploadPhotoAndGetUrl();
      if (photoUrl) {
        const userData = {
          name: name,
          age: age,
          gender: gender,
          orientation: orientation,
          city: city,
          bio: bio,
          id: id,
          avatar: photoUrl,
        };

        fetch("https://testing.teanda.ru/api/register", {
          method: "POST",
          headers: {
            "Content-Type": "application/json",
          },
          body: JSON.stringify(userData),
        })
          .then((response) => {
            if (response.status === 200) {
              console.log("200");
            } else {
              console.error("400");
            }
          })
          .catch((error) => {
            console.error("error:", error);
          });
      } else {
        setError("500");
      }
    }
  };

  if (isUserRegistered) {
    console.log("redirect");
    navigate("/menu");
  }

  return (
    <div className="index">
      <div className="overlap-group-wrapper">
        <div className="overlap">
          <img
            className="polygon"
            alt="Polygon"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/polygon-1-2@2x.png"
          />
          <p className="TELEGRAM">
            <span className="text-wrapper">Back to Telegram</span>
          </p>
        </div>
        <div className="div">
          <div className="rectangle" />
          <p className="span-wrapper">
            <label htmlFor="file" className="span">
              <p className="button-text">Choose Your Photo</p>
              <input
                type="file"
                id="file"
                accept="image/*"
                style={{ display: "none" }}
                onChange={handleFileChange}
              />
            </label>
          </p>
        </div>
        <div className="overlap-2">
          {selectedFile ? (
            <img
              className="element-1"
              src={URL.createObjectURL(selectedFile)}
              alt="Profile"
            />
          ) : (
            <div className="ellipse">
              <img
                className="element"
                alt="Element"
                src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/-------1-2-1@2x.png"
              />
            </div>
          )}
        </div>
        <div className="overlap-3">
          <p className="p">
            <span className="text-wrapper-2">Fill in all the fields</span>
          </p>
          <p className="span-wrapper-2">
            <span className="text-wrapper-3">Name</span>
          </p>
          <p className="span-wrapper-3">
            <span className="text-wrapper-4">
              <label htmlFor="Name">
                <input
                  type="text"
                  id="Name"
                  value={name}
                  placeholder="Enter your Name"
                  onChange={(e) => setName(e.target.value)}
                />
              </label>
            </span>
          </p>
          <img
            className="line"
            alt="Line"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/line-2-1@2x.png"
          />
          <p className="span-wrapper-4">
            <span className="text-wrapper-3">Age</span>
          </p>
          <p className="element-2">
            <span className="text-wrapper-4">
              <label htmlFor="Age">
                {" "}
                <input
                  type="number"
                  id="Age"
                  value={age}
                  placeholder="Enter your Age"
                  onChange={(e) => setAge(e.target.value)}
                />
              </label>
            </span>
          </p>
          <img
            className="img"
            alt="Line"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/line-2-1@2x.png"
          />
          <p className="span-wrapper-5">
            <span className="text-wrapper-3">Gender</span>
          </p>
          <p className="span-wrapper-6">
            <span className="text-wrapper-4">
              <label htmlFor="Gender">
                <select
                  placeholder="Select your Gender"
                  id="Gender"
                  value={gender}
                  onChange={(e) => setGender(e.target.value)}
                  className="select-border"
                >
                  <option value="Male">Male</option>
                  <option value="Female">Female</option>
                  {/* <option value="Other">Other</option>
          <option value="Prefer not to say">Prefer not to say</option>
          <option value="Non-binary">Non-binary</option> */}
                </select>
              </label>
            </span>
          </p>
          <img
            className="line-2"
            alt="Line"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/line-2-1@2x.png"
          />
          <p className="span-wrapper-7">
            <span className="text-wrapper-3">Orientation</span>
          </p>
          <p className="span-wrapper-8">
            <span className="text-wrapper-4">
              <label htmlFor="Orientation">
                <select
                  placeholder="Select your orientation"
                  id="Orientation"
                  value={orientation}
                  onChange={(e) => setOrientation(e.target.value)}
                  className="select-border"
                >
                  <option value="Straight">Straight</option>
                  <option value="Gay">Gay</option>
                  {/* <option value="Lesbian">Lesbian</option> */}
                  <option value="Bisexual">Bisexual</option>
                  {/* <option value="Other">Other</option> */}
                </select>
              </label>
            </span>
          </p>
          <img
            className="line-3"
            alt="Line"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/line-2-1@2x.png"
          />
          <p className="span-wrapper-9">
            <span className="text-wrapper-3">City</span>
          </p>
          <p className="span-wrapper-10">
            <span className="text-wrapper-4">
              <label htmlFor="City">
                <select
                  placeholder="Select your City"
                  id="City"
                  value={city}
                  onChange={(e) => setCity(e.target.value)}
                  className="select-border"
                >
                  <option value="New York">New York</option>
                  <option value="Los Angeles">Moscow</option>
                  <option value="Chicago">Rome</option>
                  {/* <option value="San Francisco">San Francisco</option>
          <option value="Miami">Miami</option> */}
                </select>
              </label>
            </span>
          </p>
          <img
            className="line-4"
            alt="Line"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/line-2-1@2x.png"
          />
          <p className="span-wrapper-11">
            <span className="text-wrapper-3">Bio</span>
          </p>
          <p className="span-wrapper-12">
            <span className="text-wrapper-4">
              <label htmlFor="Bio">
                <textarea
                  id="Bio"
                  placeholder="Enter your Bio"
                  value={bio}
                  onChange={(e) => setBio(e.target.value)}
                  className="text-area"
                />
              </label>

              <br />
            </span>
          </p>
          <img
            className="line-5"
            alt="Line"
            src="https://cdn.animaapp.com/projects/651aba4011cd84613b508e5b/releases/651ac821780675569006a4a1/img/line-2-1@2x.png"
          />
        </div>
        {/* <div className="form-group">
            <input id="initData" type="text" />
        </div>
        <div className="form-group">
            <input id="initDataUnsafe" type="text" />
         </div> */}
        <div className="overlap-4">
          <div className="rectangle-2" />
          <p className="span-wrapper-13">
            {error && <p className="error">{error}</p>}
            <p className="span-wrapper">
              <label htmlFor="submit" className="span">
                <p className="button-text-1" onClick={handleSubmit}>
                  Start Search
                </p>
              </label>
            </p>
          </p>
        </div>
      </div>
    </div>
  );
}

export default RegistrationPage;
