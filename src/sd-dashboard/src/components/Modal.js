import React from 'react';

const Modal = ({ handleClose, show, children }) => {
  const showHideClassName = show ? "modal display-block" : "modal display-none";

  return (
    <div className={showHideClassName}>
      <section className="modal-main">
        {children}
        <div className="modal-footer">
          <button onClick={handleClose}>close</button>
        </div>
      </section>
    </div>
  );
};

export default Modal;
